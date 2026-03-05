#include "monitor.skel.h"
#include <bpf/libbpf.h>
#include <signal.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

sqlite3 *db;

static volatile sig_atomic_t exiting = 0;

struct event {
  uint32_t pid;
  char comm[16];
  char filename[256];
};

static void sig_handler(int sig) {
  (void)sig;
  exiting = 1;
}

void save_to_db(const struct event *e) {
  time_t now = time(NULL);
  struct tm tm_info;
  char timestamp[32];
  localtime_r(&now, &tm_info);
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm_info);

  const char *sql = "INSERT INTO hids_logs (timestamp, pid, comm, filename) "
                    "VALUES (?, ?, ?, ?);";

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL hazırlanamadı: %s\n", sqlite3_errmsg(db));
    return;
  }

  sqlite3_bind_text(stmt, 1, timestamp, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, (int)e->pid);
  sqlite3_bind_text(stmt, 3, e->comm, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, e->filename, -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Kayıt eklenemedi: %s\n", sqlite3_errmsg(db));
  }

  sqlite3_finalize(stmt);
}

static int handle_event(void *ctx, void *data, size_t data_sz) {
  (void)ctx;
  (void)data_sz;
  const struct event *e = data;

  printf("\033[1;31m[HIDS ALARM]\033[0m PID: %-6d | Komut: %-10s | Dosya: %s\n",
         e->pid, e->comm, e->filename);

  save_to_db(e);

  return 0;
}

int main() {
  struct monitor_bpf *skel = NULL;
  struct ring_buffer *rb = NULL;
  char path[256];
  char *err_msg = NULL;
  int rc;

  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);

  rc = sqlite3_open("hids_events.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Veritabanı açılamadı: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  const char *create_sql = "CREATE TABLE IF NOT EXISTS hids_logs("
                           "id        INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "timestamp TEXT, "
                           "pid       INTEGER, "
                           "comm      TEXT, "
                           "filename  TEXT);";

  rc = sqlite3_exec(db, create_sql, 0, 0, &err_msg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tablo oluşturulamadı: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }

  printf("İzlemek istediğin klasörü gir: ");
  fflush(stdout);
  if (!fgets(path, sizeof(path), stdin)) {
    fprintf(stderr, "Yol okunamadı.\n");
    sqlite3_close(db);
    return 1;
  }

  size_t len = strlen(path);
  if (len > 0 && path[len - 1] == '\n')
    path[len - 1] = '\0';

  skel = monitor_bpf__open();
  if (!skel) {
    fprintf(stderr, "eBPF iskeleti açılamadı!\n");
    sqlite3_close(db);
    return 1;
  }

  strncpy(skel->bss->target_path, path, sizeof(skel->bss->target_path) - 1);
  skel->bss->target_path[sizeof(skel->bss->target_path) - 1] = '\0';

  if (monitor_bpf__load(skel)) {
    fprintf(stderr, "eBPF yüklenemedi!\n");
    goto cleanup;
  }

  if (monitor_bpf__attach(skel)) {
    fprintf(stderr, "eBPF attach başarısız!\n");
    goto cleanup;
  }

  rb = ring_buffer__new(bpf_map__fd(skel->maps.rb), handle_event, NULL, NULL);
  if (!rb) {
    fprintf(stderr, "Ring buffer oluşturulamadı!\n");
    goto cleanup;
  }

  printf("\n--- %s İzleniyor | Durdurmak için Ctrl+C ---\n\n", path);

  while (!exiting) {
    rc = ring_buffer__poll(rb, 100);
    if (rc < 0 && rc != -EINTR) {
      fprintf(stderr, "Ring buffer poll hatası: %d\n", rc);
      break;
    }
  }

  printf("\nDurduruluyor, kaynaklar temizleniyor...\n");

cleanup:
  ring_buffer__free(rb);
  monitor_bpf__destroy(skel);
  sqlite3_close(db);
  return 0;
}
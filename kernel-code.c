#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char LICENSE[] SEC("license") = "GPL";

struct event {
  u32 pid;
  char comm[16];
  char filename[256];
};

struct {
  __uint(type, BPF_MAP_TYPE_RINGBUF);
  __uint(max_entries, 256 * 1024);
} rb SEC(".maps");

volatile char target_path[256];

SEC("tracepoint/syscalls/sys_enter_openat")
int handle_openat(struct trace_event_raw_sys_enter *ctx) {
  char filename[256];
  const char *name_ptr = (const char *)ctx->args[1];

  long ret = bpf_probe_read_user_str(filename, sizeof(filename), name_ptr);
  if (ret <= 0)
    return 0;

  if (target_path[0] != '\0') {
    if (bpf_strncmp(filename, 256, (const char *)target_path) != 0)
      return 0;
  }
  struct event *e;
  e = bpf_ringbuf_reserve(&rb, sizeof(*e), 0);
  if (!e)
    return 0;

  e->pid = bpf_get_current_pid_tgid() >> 32;
  bpf_get_current_comm(e->comm, sizeof(e->comm));
  bpf_probe_read_user_str(e->filename, sizeof(e->filename), name_ptr);

  bpf_ringbuf_submit(e, 0);

  return 0;
}
#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char LICENSE[] SEC("license") = "GPL";

struct event {
  u32 pid;
  char comm[16];
  u32 dest_ip;
  u16 dest_port;
};

struct {
  __uint(type, BPF_MAP_TYPE_RINGBUF);
  __uint(max_entries, 256 * 1024);
} rb_net SEC(".maps");

SEC("tracepoint/syscalls/sys_enter_connect")
int handle_connect(struct trace_event_raw_sys_enter *ctx) {
  struct sockaddr_in *addr;
  struct event *e;

  addr = (struct sockaddr_in *)ctx->args[1];

  sa_family_t family;
  if (bpf_probe_read_user(&family, sizeof(family), &addr->sin_family) < 0)
    return 0;
  if (family != 2)
    return 0;

  e = bpf_ringbuf_reserve(&rb_net, sizeof(*e), 0);
  if (!e)
    return 0;

  e->pid = bpf_get_current_pid_tgid() >> 32;
  bpf_get_current_comm(&e->comm, sizeof(e->comm));

  if (bpf_probe_read_user(&e->dest_ip, sizeof(e->dest_ip),
                          &addr->sin_addr.s_addr) < 0 ||
      bpf_probe_read_user(&e->dest_port, sizeof(e->dest_port),
                          &addr->sin_port) < 0) {
    bpf_ringbuf_discard(e, 0);
    return 0;
  }

  bpf_ringbuf_submit(e, 0);

  return 0;
}
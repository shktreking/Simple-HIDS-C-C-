APP      = monitor
BPF_C    = kernel-code.c
BPF_OBJ  = monitor.bpf.o
SKEL_H   = monitor.skel.h
MAIN_C   = main.c
MAIN_OBJ = main.o


NET_BPF_C   = network_bpf.c
NET_BPF_OBJ = network.bpf.o


CLANG    ?= clang
CC       ?= gcc
BPFTOOL  ?= bpftool

CFLAGS     := -g -O2 -Wall -Wextra
BPF_CFLAGS := -g -O2 -target bpf -D__TARGET_ARCH_x86


LDFLAGS := -lbpf -lelf -lz -lsqlite3

all: $(APP)


$(BPF_OBJ): $(BPF_C)
	$(CLANG) $(BPF_CFLAGS) -c $< -o $@

$(NET_BPF_OBJ): $(NET_BPF_C)
	$(CLANG) $(BPF_CFLAGS) -c $< -o $@

$(SKEL_H): $(BPF_OBJ)
	$(BPFTOOL) gen skeleton $< > $@

$(MAIN_OBJ): $(MAIN_C) $(SKEL_H)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(APP): $(MAIN_OBJ) $(NET_BPF_OBJ)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(LDFLAGS) -o $@

clean:
	rm -f $(APP) $(MAIN_OBJ) $(BPF_OBJ) $(NET_BPF_OBJ) $(SKEL_H)

.PHONY: all clean
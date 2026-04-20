#include "syscall.h"

static inline long sys_write(int fd, const char *buf, size_t len) {
  return syscall3(1, fd, (long)buf, len);
}

static inline void sys_exit(int status) { syscall2(60, status, 0); }

const char MSG[] = "Hello using musl's syscall() and SYS_ constants!\n";

void _start(void) {
  sys_write(1, MSG, sizeof(MSG) - 1);

  sys_exit(0);
}

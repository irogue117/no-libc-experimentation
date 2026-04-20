#include "syscall.h"

static inline long sys_write(int fd, const char *buf, size_t len) {
  return syscall3(SYS_write, fd, (long)buf, len);
}

static inline void sys_exit(int status) { syscall2(SYS_exit, status, 0); }

const char MSG[] = "NO LIBC B)\n";

struct utsname u = {0};

void _start(void) {
  syscall1(SYS_uname, (long)&u);

  const char arch_str[] = "Architecture: ";
  sys_write(STDOUT, arch_str, sizeof(arch_str) - 1);
  sys_write(STDOUT, u.machine, sizeof(u.machine) - 1);
  sys_write(STDOUT, "\n", 1);

  sys_write(STDOUT, MSG, sizeof(MSG) - 1);

  sys_exit(0);
}

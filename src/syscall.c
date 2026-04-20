#include "syscall.h"

long syscall6(long nr, long a1, long a2, long a3, long a4, long a5, long a6) {
  long ret;

  register long r10 __asm__("r10") = a4;
  register long r8 __asm__("r8") = a5;
  register long r9 __asm__("r9") = a6;

  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(nr), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8),
                     "r"(r9)
                   : "rcx", "r11", "memory");

  return ret;
}

long syscall0(long nr) { return syscall6(nr, 0, 0, 0, 0, 0, 0); }

long syscall1(long nr, long a1) { return syscall6(nr, a1, 0, 0, 0, 0, 0); }

long syscall2(long nr, long a1, long a2) {
  return syscall6(nr, a1, a2, 0, 0, 0, 0);
}

long syscall3(long nr, long a1, long a2, long a3) {
  return syscall6(nr, a1, a2, a3, 0, 0, 0);
}

long syscall4(long nr, long a1, long a2, long a3, long a4) {
  return syscall6(nr, a1, a2, a3, a4, 0, 0);
}

long syscall5(long nr, long a1, long a2, long a3, long a4, long a5) {
  return syscall6(nr, a1, a2, a3, a4, a5, 0);
}

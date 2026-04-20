#ifndef MY_SYSCALL_H
#define MY_SYSCALL_H

typedef __SIZE_TYPE__ size_t;

enum {
  SYS_write = 1,
  SYS_exit = 60,
  SYS_exit_group = 231,
};

long syscall0(long nr);
long syscall1(long nr, long a1);
long syscall2(long nr, long a1, long a2);
long syscall3(long nr, long a1, long a2, long a3);
long syscall4(long nr, long a1, long a2, long a3, long a4);
long syscall5(long nr, long a1, long a2, long a3, long a4, long a5);
long syscall6(long nr, long a1, long a2, long a3, long a4, long a5, long a6);

#endif

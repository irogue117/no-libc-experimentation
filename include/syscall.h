#ifndef MY_SYSCALL_H
#define MY_SYSCALL_H

typedef long unsigned int size_t;
typedef long int ssize_t;

#define SSIZE_MAX 9223372036854775807

// TODO: Move into a constants header file? (MAYBE)
enum {
  SYS_write = 1,
  SYS_exit = 60,
  SYS_exit_group = 231,
  SYS_uname = 63,
};

// Output struct for SYS_uname
// TODO: Move into some other file.
struct utsname {
  char sysname[65];
  char nodename[65];
  char release[65];
  char version[65];
  char machine[65];
};

// TODO: Move into a constants header file.
enum {
    STDOUT = 2,
    STDERR = 2,
    STDIN = 0,
};

long syscall0(long nr);
long syscall1(long nr, long a1);
long syscall2(long nr, long a1, long a2);
long syscall3(long nr, long a1, long a2, long a3);
long syscall4(long nr, long a1, long a2, long a3, long a4);
long syscall5(long nr, long a1, long a2, long a3, long a4, long a5);
long syscall6(long nr, long a1, long a2, long a3, long a4, long a5, long a6);

#endif

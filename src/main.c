#include "syscall.h"

static inline long sys_write(int fd, const char *buf, size_t len) {
  return syscall3(SYS_write, fd, (long)buf, len);
}

static inline void sys_exit(int status) { syscall2(SYS_exit, status, 0); }

const char MSG[] = "NO LIBC B)\n";
const char arch_str[] = "x86_64";
const char arch_wrong_msg[] =
    "Wrong CPU architecture, this only works on x86_64.\n";

struct utsname u = {0};

static _Bool arr_equal(const char *arr1, const size_t len1, const char *arr2,
                       const size_t len2) {
  size_t i = 0;

  if (len1 != len2) {
    return 0;
  }

  for (i = 0; i < len1; i++) {
    if (arr1[i] != arr2[i]) {
      return 0;
    }
  }

  return 1;
}

// Returns error if len > SSIZE_MAX.
static ssize_t sentinel_index(const char *arr, const size_t len,
                              const char sentinel) {
  if (len > SSIZE_MAX) {
    return -1;
  }
  size_t i;

  for (i = 0; i < len; i++) {
    if (arr[i] == sentinel) {
      return i;
    }
  }

  return -1;
}

void _start(void) {
  syscall1(SYS_uname, (long)&u);

  ssize_t str_size = sentinel_index(u.machine, sizeof(u.machine), '\0');
  if (str_size == -1) {
    goto exit_error;
  }

  int arch_match =
      arr_equal(arch_str, sizeof(arch_str) - 1, u.machine, str_size);

  if (!arch_match) {
    sys_write(STDERR, arch_wrong_msg, sizeof(arch_wrong_msg) - 1);
    goto exit;
  }

  sys_write(STDOUT, MSG, sizeof(MSG) - 1);

exit:
  sys_exit(0);

exit_error:
  sys_exit(1);
}

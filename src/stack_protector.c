#include "stack_protector.h"
#include "syscall.h"

/* Linux x86-64 only */

typedef __SIZE_TYPE__ size_t;

__attribute__((noreturn)) void __stack_chk_fail(void) {
  static const char msg[] = "stack smashing detected EXITING ALL PROCESS THREADS\n";

  /* best effort */
  syscall3(SYS_write, 2, (long)msg, sizeof(msg) - 1);

  /* exit the whole process */
  syscall1(SYS_exit_group, 127);

  /* fallback if exit_group somehow returns */
  __builtin_trap();
  for (;;)
    ;
}

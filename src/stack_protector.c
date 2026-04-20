#include "stack_protector.h"
#include "syscall.h"

// Linux x86-64 only

typedef __SIZE_TYPE__ size_t;

__attribute__((noreturn)) void __stack_chk_fail(void) {
  static const char msg[] =
      "stack smashing detected EXITING ALL PROCESS THREADS\n";

  // Best effort (try, but not important)
  syscall3(SYS_write, 2, (long)msg, sizeof(msg) - 1);

  // Exit all threads in process.
  syscall1(SYS_exit_group, 127);

  // Tells compiler to do whatever it can to kill the process e.g run illegal
  // assembly command.
  __builtin_trap();
  for (;;)
    ;
}

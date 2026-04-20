#ifndef STACK_PROTECTOR_H
#define STACK_PROTECTOR_H

/* Use a compiler-provided type */
typedef __SIZE_TYPE__ size_t;

/*
 * Stack canary value used by -fstack-protector
 * Must be globally visible.
 */
extern unsigned long __stack_chk_guard;

/*
 * Called when stack corruption is detected.
 * Must not return.
 */
__attribute__((noreturn)) void __stack_chk_fail(void);

#endif

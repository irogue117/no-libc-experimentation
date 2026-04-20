#include "../src/stack_protector.h"

void smash(void)
{
    char buf[8];

    for (size_t i = 0; i < 64; ++i) {
        buf[i] = 'A';
    }
}


void _start(void) {
    smash();
}

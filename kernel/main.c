#include "debug.h"
#include "timer.h"

#define NORETURN
#define ADDR(X) (*((volatile unsigned int *)(X)))
#define VECTOR_BASE 0x0

void init_vector_table();
void init_uart();

void NORETURN kernel_start() {
    debug_puts("Booting kernel\n");
    debug_puts("Initializing Vector table");
    init_vector_table();
    debug_puts(" Done\n");
    debug_puts("Initializing Timer");
    init_timer();
    ADDR(VECTOR_BASE + 0x18) = (unsigned int)handle_timer_irq;
    debug_puts(" Done\n");
}

void init_vector_table() {
    for (int i = 0; i < 8; i++) ADDR(i) = 0;
}

#include "timer.h"

#include "debug.h"
#include "peripheral_base.h"

// APB Clock is ~250 Mhz (I think...)
// The speed depends on the system clock and it can change
// We want an interrupt every 100ms
// System Clock (1GHz) / 0xFF (Prescaler) / 100 = 39215
#define TIMER_LOAD_VALUE 39215

#define TIMER_ENABLED 1 << 7
#define TIMER_INTERRUPT 1 << 5
#define TIMER_DISABLE_IN_DEBUG 1 << 8
// Timer Prescale is 8 bit
#define TIMER_PRESCALER(X) ((X) << 16)

void init_timer() {
    volatile int *timer_load = (volatile int *)TIMER_ARM_BASE + 0x400;
    volatile int *timer_control = (volatile int *)TIMER_ARM_BASE + 0x408;

    *timer_load = TIMER_LOAD_VALUE;
    *timer_control = TIMER_PRESCALER(0xFF) | TIMER_ENABLED | TIMER_INTERRUPT |
                     TIMER_DISABLE_IN_DEBUG;
}

// Maybe implement in assembly
void handle_timer_irq() { debug_puts("IRQ\n"); }
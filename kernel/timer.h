#ifndef H_KERNEL_TIMER
#define H_KERNEL_TIMER

#define KERNEL_TIMER_TIME 1000

void init_timer();
void handle_timer_irq();

#endif
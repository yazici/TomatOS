#ifndef TOMATKERNEL_TIMER_H
#define TOMATKERNEL_TIMER_H

#include <stdint.h>
#include <error.h>
#include "interrupts.h"

/**
 * Will set up the interrupt timer, anything which wants to run every
 * X millis will go in here
 *
 * @remark
 * The resolution of this is about ~10 millis
 */
error_t timer_init();

// TODO: Support one-shot timers

/**
 * Add an interval timer
 *
 * @param handler   [IN] The handler to call on the timer
 * @param time      [IN] The time in millis for each interval
 */
error_t timer_add(interrupt_handler_f handler, uint64_t time);

/**
 * The timer interrupt stub, calls the timer_interrupt_handler
 */
extern void timer_interrupt_stub();

/**
 * The timer interrupt handler, called from the stub
 */
void timer_interrupt_handler(registers_t regs);

#endif //TOMATKERNEL_TIMER_H

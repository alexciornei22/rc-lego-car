#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>


/**
 * Initialize Timer 0 (8-bit) in Fast PWM mode.
 */
void Timer0_init_pwm();

/**
 * Initialize Timer 2 (8-bit) for 1000Hz interrupts
*/
void Timer2_init_1000hz();

#endif // TIMERS_H_


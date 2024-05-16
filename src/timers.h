#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>


/**
 * Initialize Timer 0 (8-bit) in Fast PWM mode.
 */
void Timer0_init_pwm();

/**
 * Initialize Timer 1 (16-bit) for input capture event
*/
void Timer1_init_input_capture();

/**
 * Initialize Timer 2 (8-bit) for 1000Hz interrupts
*/
void Timer2_init_1Khz();

#endif // TIMERS_H_


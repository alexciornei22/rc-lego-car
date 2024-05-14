#include <stdio.h>
#include <avr/io.h>

#include "timers.h"


void Timer0_init_pwm()
{
    // set PD6(OC0A) as output
    DDRD |= _BV(PD6);

    // set fast PWM mode
    TCCR0A |= _BV(WGM00);
    TCCR0A |= _BV(WGM01);

    // set non-inverting mode
    TCCR0A |= _BV(COM0A1);

    // set 1024 prescaler
    TCCR0B |= _BV(CS00);
    TCCR0B |= _BV(CS02);

    OCR0A = 0;
}

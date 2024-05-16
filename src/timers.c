#include <avr/io.h>
#include <avr/interrupt.h>

#include "timers.h"

volatile uint16_t millis = 0;

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

    OCR0A = 127;
}

void Timer2_init_1000hz()
{
    cli();
    // set CTC mode
    TCCR2A |= _BV(WGM21);

    // set 64 prescaler
    TCCR2B |= _BV(CS22);
    
    // set compare register for 1000Hz
    OCR2A |= 250;

    // set interrupt
    TIMSK2 |= _BV(OCIE2A);

    sei();
}

ISR(TIMER2_COMPA_vect)
{
    millis ++;
}
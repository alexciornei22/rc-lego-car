#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timers.h"

volatile uint16_t millis = 0;
volatile uint16_t buzzer_millis = 0;
volatile uint16_t ultrasonic_sensor_micros = 0;
volatile bool distance_updated = false;

void Timer0_init_phase_correct_pwm()
{
    // set PD6(OC0A)
    // and PD5(OC1A)
    // as output
    DDRD |= _BV(PD6);
    DDRD |= _BV(PD5);

    // set Phase Correct PWM mode
    TCCR0A |= _BV(WGM00);

    // set OC0A/OC1A when up-counting
    // TCCR0A |= _BV(COM0A0);
    TCCR0A |= _BV(COM0A1);
    // TCCR0A |= _BV(COM0B0);
    TCCR0A |= _BV(COM0B1);

    // set 1024 prescaler
    TCCR0B |= _BV(CS00);
    TCCR0B |= _BV(CS02);

    OCR0A = 0;
    OCR0B = 0;
}

void Timer1_init_input_capture()
{
    cli();

    // OC1A/OC0B disconnected, normal mode
    TCCR1A = 0;

    // set input capture noise canceler
    TCCR1B |= _BV(ICNC1);
    // set falling edge trigger
    TCCR1B &= ~_BV(ICES1);

    // set 8 prescaler
    TCCR1B |= _BV(CS11);

    // set input capture interrupt
    TIMSK1 |= _BV(ICIE1);
    
    sei();
}

ISR(TIMER1_CAPT_vect)
{
    ultrasonic_sensor_micros = ICR1 / 2;
    distance_updated = true;
}

void Timer2_init_1Khz()
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
    millis++;
    buzzer_millis++;
}

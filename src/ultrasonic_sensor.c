#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ultrasonic_sensor.h"

extern volatile uint16_t ultrasonic_sensor_micros;
extern bool distance_updated;

void ultrasonic_sensor_init_gpio()
{
    // set ECHO pin as input
    DDRB &= ~_BV(PB0);
	PORTB |= _BV(PB0);

    // set TRIG pin as output
	DDRD |= _BV(PD7);
	PORTD &= ~_BV(PD7);
}

void ultrasonic_sensor_trigger()
{
    // set TRIG pin HIGH for a few microseconds
    PORTD |= _BV(PD7);
	_delay_us(5);
	PORTD &= ~_BV(PD7);

    // reset Timer 1 counter
	TCNT1 = 0;
}

void ultrasonic_sensor_clear_update_flag()
{
    distance_updated = false;
}

uint16_t ultrasonic_sensor_get_distance()
{
    return (ultrasonic_sensor_micros * .0343) / 2;
}

bool ultrasonic_sensor_update()
{
    return distance_updated;
}
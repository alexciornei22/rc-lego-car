#include <avr/io.h>

#include "leds.h"

#define BLUETOOTH_LED PB5

#define HEADLIGHT0 PC0
#define HEADLIGHT1 PC1
#define HAZARDLIGHT0 PC2
#define HAZARDLIGHT1 PC3

void leds_init()
{
    // set bluetooth connection pin to output
    // and set to LOW
    DDRB |= _BV(BLUETOOTH_LED);
    PORTB &= ~_BV(BLUETOOTH_LED);

    // set car lights to output and set LOW
    DDRC |= _BV(HEADLIGHT0);
    DDRC |= _BV(HEADLIGHT1);
    DDRC |= _BV(HAZARDLIGHT0);
    DDRC |= _BV(HAZARDLIGHT1);
    PORTC &= ~_BV(HEADLIGHT0);
    PORTC &= ~_BV(HEADLIGHT1);
    PORTC &= ~_BV(HAZARDLIGHT0);
    PORTC &= ~_BV(HAZARDLIGHT1);
}

void bluetooth_conn_led_enable()
{
    PORTB |= _BV(BLUETOOTH_LED);
}

void bluetooth_conn_led_disable()
{
    PORTB &= ~_BV(BLUETOOTH_LED);
}

void headlights_enable()
{
    PORTC |= _BV(HEADLIGHT0);
    PORTC |= _BV(HEADLIGHT1);
}

void headlights_disable()
{
    PORTC &= ~_BV(HEADLIGHT0);
    PORTC &= ~_BV(HEADLIGHT1);
}

void hazardlights_enable()
{
    PORTC |= _BV(HAZARDLIGHT0);
    PORTC |= _BV(HAZARDLIGHT1);
}

void hazardlights_disable()
{
    PORTC &= ~_BV(HAZARDLIGHT0);
    PORTC &= ~_BV(HAZARDLIGHT1);
}

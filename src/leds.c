#include <avr/io.h>
#include <stdbool.h>

#include "leds.h"

#define BLUETOOTH_LED PB5

#define HEADLIGHTS PC0
#define SIGNAL_RIGHT PC1
#define SIGNAL_LEFT PC2

bool hazards_on = false;

void leds_init()
{
    // set bluetooth connection pin to output
    // and set to LOW
    DDRB |= _BV(BLUETOOTH_LED);
    PORTB &= ~_BV(BLUETOOTH_LED);

    // set car lights to output
    DDRC |= _BV(HEADLIGHTS);
    DDRC |= _BV(SIGNAL_RIGHT);
    DDRC |= _BV(SIGNAL_LEFT);

    headlights_disable();
    hazardlights_disable();
}

void bluetooth_conn_led_enable()
{
    PORTB |= _BV(BLUETOOTH_LED);
}

void bluetooth_conn_led_disable()
{
    PORTB &= ~_BV(BLUETOOTH_LED);
}

void headlights_disable()
{
    PORTC |= _BV(HEADLIGHTS);
}

void headlights_enable()
{
    PORTC &= ~_BV(HEADLIGHTS);
}

void hazardlights_disable()
{
    PORTC |= _BV(SIGNAL_RIGHT);
    PORTC |= _BV(SIGNAL_LEFT);
}

void hazardlights_toggle()
{
    PORTC ^= _BV(SIGNAL_RIGHT);
    PORTC ^= _BV(SIGNAL_LEFT);
}

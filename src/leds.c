#include <avr/io.h>

#include "leds.h"

void init_bluetooth_conn_led()
{
    // set bluetooth connection pin to output
    // and set to low
    DDRC |= _BV(PC3);
    PORTC &= ~_BV(PC3);
}
#include <avr/io.h>

#include "buzzer.h"

extern volatile uint16_t buzzer_millis;
static uint16_t buzzer_frequency = 0;

void buzzer_init_gpio()
{
    // set buzzer pin as output and set LOW
    DDRD |= _BV(PD4);
    PORTD &= ~_BV(PD4);
}

void buzzer_turn_on()
{
    // set buzzer pin HIGH
    PORTD |= _BV(PD4);
}

void buzzer_turn_off()
{
    // set buzzer pin LOW
    PORTD &= ~_BV(PD4);
}

void buzzer_use()
{
	if (buzzer_millis >= buzzer_frequency) {
		buzzer_millis = 0;
	}

	if ((buzzer_frequency > 0) & (buzzer_millis <= 100)) {
		buzzer_turn_on();
	} else {
		buzzer_turn_off();
	}
}

void buzzer_update_frequency_for_distance(uint16_t distance)
{
    if (distance >= 40) {
        buzzer_frequency = 0;
        return;
    }

    if (distance < 18) {
        buzzer_frequency = 100;
        return;
    }

    if (distance < 25) {
        buzzer_frequency = 200;
        return;
    }

    if (distance < 30) {
        buzzer_frequency = 300;
        return;
    }

    if (distance < 40) {
        buzzer_frequency = 500;
        return;
    }
}

#include <avr/io.h>

#include "adc.h"

void adc_init()
{
    // channel 0
    ADMUX = 0;
    // AVcc with external capacitor at AREF PIN
    ADMUX |= _BV(REFS0);

    ADCSRA = 0;
    // set 128 prescaler
    ADCSRA |= _BV(ADPS0);
    ADCSRA |= _BV(ADPS1);
    ADCSRA |= _BV(ADPS2);
    // enable ADC
    ADCSRA |= _BV(ADEN);
}

uint16_t adc_get_light_value()
{
	// start conversion
	ADCSRA |= (1 << ADSC);

	// wait until conversion is complete
	while ((ADCSRA & (1 << ADSC)));

	return ADC;
}

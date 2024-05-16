#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/**
 * Initialize Analog-Digital Converter
*/
void adc_init();

/**
 * Get photoresistor light value from ADC
*/
uint16_t adc_get_light_value();

#endif // ADC_H_

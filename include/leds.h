#ifndef LEDS_H_
#define LEDS_H_

/**
 * Set bluetooth connection indicator LED pin as output
*/
void leds_init();

void bluetooth_conn_led_enable();
void bluetooth_conn_led_disable();

void headlights_enable();
void headlights_disable();

void hazardlights_toggle();
void hazardlights_disable();

#endif // LEDS_H_

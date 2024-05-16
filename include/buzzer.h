#ifndef BUZZER_H_
#define BUZZER_H_

#include <stdint.h>

/**
 * Initialize buzzer controlling pin
*/
void buzzer_init_gpio();

void buzzer_turn_on();

void buzzer_turn_off();

/**
 * triggers buzzer to ping at the set frequency
 * according to the distance to obstacles
*/
void buzzer_use();

/**
 * Updates the frequency at which the buzzer should ping
 * based on a given distance
*/
void buzzer_update_frequency_for_distance(uint16_t distance);

#endif // BUZZER_H_

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include <stdint.h>

/**
 * Initialize ECHO and TRIG pins for ultrasonic sensor
*/
void ultrasonic_sensor_init_gpio();

/**
 * Send trigger signal to ultrasonic sensor
 * through TRIG pin
*/
void ultrasonic_sensor_trigger();

/**
 * Computes distance based on signal travel time
*/
uint16_t ultrasonic_sensor_get_distance();

#endif // ULTRASONIC_SENSOR_H_

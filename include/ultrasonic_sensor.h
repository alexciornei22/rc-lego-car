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
 * Returns true if the distance updated flag is set
*/
bool ultrasonic_sensor_update();

/**
 * Clears the distance_updated flag
 * (this should be called after getting the distance)
*/
void ultrasonic_sensor_clear_update_flag();

/**
 * Computes distance based on signal travel time
*/
uint16_t ultrasonic_sensor_get_distance();

#endif // ULTRASONIC_SENSOR_H_

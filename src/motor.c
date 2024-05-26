#include <avr/io.h>
#include <stdbool.h>

#include "motor.h"

enum direction motor_direction = FORWARDS;
uint8_t motor_throttle = 0;

void update_direction(enum direction dir)
{
    motor_direction = dir;
    if (dir == FORWARDS) {
        OCR0A = motor_throttle;
        OCR0B = 0;
    } else {
        OCR0A = 0;
        OCR0B = motor_throttle;
    }
}

void update_throttle_input(uint8_t throttle)
{
    motor_throttle = throttle;
    if (motor_direction == FORWARDS) {
        OCR0A = throttle;
    } else {
        OCR0B = throttle;
    }
}
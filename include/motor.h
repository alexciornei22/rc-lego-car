#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

enum direction {
    FORWARDS,
    BACKWARDS
};

void update_direction(enum direction dir);

void update_throttle_input(uint8_t throttle);

#endif // MOTOR_H_

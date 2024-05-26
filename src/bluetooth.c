#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "bluetooth.h"
#include "usart.h"
#include "leds.h"
#include "motor.h"

#define MOD_CONNECTED "+CONNECTED"
#define MOD_DISCONNECTED "+DISCONNECTED"

#define USR_COMMAND_LEN 3
#define USR_DIRECTION "DIR"
#define USR_THROTTLE "THR"
#define USR_HEADLIGHTS "HDL"
#define USR_HAZARDLIGHTS "HZL"
#define USR_PARKING_SENSOR "PRK"
#define USR_LIGHT_SENSOR "LIT"

extern bool parking_sensor_enable;
extern bool light_sensor_enable;
extern bool hazards_on;


void _handle_module_command(char *command);
void _handle_user_command(char *command);

void _handle_direction_command(char *value_string);
void _handle_throttle_command(char *value_string);
void _handle_headlights_command(char *value_string);
void _handle_hazardlights_command(char *value_string);
void _handle_parking_sensor_command(char *value_string);
void _handle_light_sensor_command(char *value_string);

void _trim_crlf(char *command);

void bluetooth_init()
{
    USART0_print_crlf("AT+DEFAULT");
	USART0_print_crlf("AT+NAMEPORSCHE");
	USART0_print_crlf("AT+NLPORSCHE");
	USART0_print_crlf("AT+NFPORSCHE");
}

void handle_bluetooth_command(char *command)
{
    _trim_crlf(command);

    if (*command == '+') {
        _handle_module_command(command);
        return;
    }

    _handle_user_command(command);
}

void _trim_crlf(char *command)
{
    size_t len = strlen(command);
    command[len - 1] = '\0';
    command[len - 2] = '\0';
}

void _handle_module_command(char *command)
{
    if (!strcmp(command, MOD_CONNECTED)) {
        bluetooth_conn_led_enable();
    }

    if (!strcmp(command, MOD_DISCONNECTED)) {
        bluetooth_conn_led_disable();
    }
}

void _handle_user_command(char *command)
{
    if (!strncmp(command, USR_DIRECTION, USR_COMMAND_LEN)) {
        _handle_direction_command(command + USR_COMMAND_LEN);
    }

    if (!strncmp(command, USR_THROTTLE, USR_COMMAND_LEN)) {
        _handle_throttle_command(command + USR_COMMAND_LEN);
    }

    if (!strncmp(command, USR_HEADLIGHTS, USR_COMMAND_LEN)) {
        _handle_headlights_command(command + USR_COMMAND_LEN);
    }

    if (!strncmp(command, USR_HAZARDLIGHTS, USR_COMMAND_LEN)) {
        _handle_hazardlights_command(command + USR_COMMAND_LEN);
    }

    if (!strncmp(command, USR_PARKING_SENSOR, USR_COMMAND_LEN)) {
        _handle_parking_sensor_command(command + USR_COMMAND_LEN);
    }

    if (!strncmp(command, USR_LIGHT_SENSOR, USR_COMMAND_LEN)) {
        _handle_light_sensor_command(command + USR_COMMAND_LEN);
    }
}

void _handle_direction_command(char *value_string)
{
    uint8_t dir = atoi(value_string);

    if (dir == 1) {
        update_direction(FORWARDS);
    } else {
        update_direction(BACKWARDS);
    }
}

void _handle_throttle_command(char *value_string)
{
    uint8_t value = atoi(value_string);
    
    update_throttle_input(value);
}

void _handle_headlights_command(char *value_string)
{
    uint8_t value = atoi(value_string);
    
    if (value) {
        headlights_enable();
    } else {
        headlights_disable();
    }
}

void _handle_hazardlights_command(char *value_string)
{
    uint8_t value = atoi(value_string);
    
    if (value) {
        hazards_on = true;
    } else {
        hazards_on = false;
    }
}

void _handle_parking_sensor_command(char *value_string)
{
    uint8_t value = atoi(value_string);
    
    if (value) {
        parking_sensor_enable = true;
    } else {
        parking_sensor_enable = false;
    }
}

void _handle_light_sensor_command(char *value_string)
{
    uint8_t value = atoi(value_string);
    
    if (value) {
        light_sensor_enable = true;
    } else {
        light_sensor_enable = false;
    }
}

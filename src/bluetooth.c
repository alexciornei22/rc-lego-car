#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "bluetooth.h"
#include "usart.h"
#include "leds.h"

#define MOD_CONNECTED "+CONNECTED"
#define MOD_DISCONNECTED "+DISCONNECTED"

#define USR_COMMAND_LEN 3
#define USR_HEADLIGHTS "HDL"
#define USR_HAZARDLIGHTS "HZL"
#define USR_PARKING_SENSOR "PRK"
#define USR_LIGHT_SENSOR "LIT"

void _handle_module_command(char *command);
void _handle_user_command(char *command);

void _handle_headlights_command(char *value_string);

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
    if (!strncmp(command, USR_HEADLIGHTS, USR_COMMAND_LEN)) {
        _handle_headlights_command(command + USR_COMMAND_LEN);
    }
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

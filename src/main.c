#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "usart.h"
#include "timers.h"
#include "leds.h"
#include "bluetooth.h"
#include "adc.h"
#include "ultrasonic_sensor.h"
#include "buzzer.h"

#define BAUD_RATE 9600
#define LIGHT_THRESHOLD 500

extern volatile uint16_t millis;

bool parking_sensor_enable = false;
bool light_sensor_enable = false;

int main()
{
	// Initialize USART
	USART0_init(CALC_USART_UBRR(BAUD_RATE));

	ultrasonic_sensor_init_gpio();
	buzzer_init_gpio();

	Timer0_init_pwm();
	Timer1_init_input_capture();
	Timer2_init_1Khz();

	leds_init();
	adc_init();
	bluetooth_init();

	while (1) {

		if (parking_sensor_enable) {
			buzzer_use();
		} else {
			buzzer_turn_off();
		}

		if (ultrasonic_sensor_update()) {
			uint16_t distance = ultrasonic_sensor_get_distance();
			buzzer_update_frequency_for_distance(distance);
			ultrasonic_sensor_clear_update_flag();

			// char buffer[30];
			// sprintf(buffer, "Distance: %u", distance);
			// USART0_print_crlf(buffer);
		}

		if (millis >= 250) {
			millis = 0;
			
			if (light_sensor_enable) {
				uint16_t light_value = adc_get_light_value();
				if (light_value < LIGHT_THRESHOLD) {
					headlights_enable();
				} else {
					headlights_disable();
				}
			}

			ultrasonic_sensor_trigger();
		}

		if (USART0_string_received()) {
			char command[USART_BUFFER_MAX_LEN];
			strncpy(command, USART0_read_buffer(), USART_BUFFER_MAX_LEN); 
			USART0_print(command);
			handle_bluetooth_command(command);
		}
	}

	return 0;
}

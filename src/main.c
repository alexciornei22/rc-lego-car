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

extern volatile uint16_t millis;

bool light_low = false;

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

		buzzer_use();

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
			
			uint16_t result = adc_get_light_value();
			// char buffer[30];
			// sprintf(buffer, "Light: %u", result);
			// USART0_print_crlf(buffer);

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

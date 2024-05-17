#include <stdio.h>
#include <stdbool.h>

#include "usart.h"
#include "timers.h"
#include "leds.h"
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

	init_bluetooth_conn_led();
	adc_init();

	USART0_print_crlf("AT+NAMELEGO-CAR");
	USART0_print_crlf("AT+NLLEGO-CAR");

	while (1) {

		buzzer_use();

		if (ultrasonic_sensor_update()) {
			uint16_t distance = ultrasonic_sensor_get_distance();
			buzzer_update_frequency_for_distance(distance);
			ultrasonic_sensor_clear_update_flag();
		}

		if (millis >= 250) {
			millis = 0;
			
			uint16_t result = adc_get_light_value();

			ultrasonic_sensor_trigger();
		}

		if (USART0_string_received()) {
			const char* buffer = USART0_read_buffer();
			USART0_print(buffer);
		}
	}

	return 0;
}

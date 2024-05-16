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

	USART0_print("AT+NAMELEGO-CAR\r\n");
	USART0_print("AT+NLLEGO-CAR\r\n");

	char usart_buffer[30];

	while (1) {

		buzzer_use();
	
		if (millis >= 250) {
			millis = 0;
			
			// uint16_t result = adc_get_light_value();
			// sprintf(usart_buffer, "%u %u\r\n", result, millis);
			// USART0_print(usart_buffer);

			ultrasonic_sensor_trigger();

			uint16_t distance = ultrasonic_sensor_get_distance();
			buzzer_update_frequency_for_distance(distance);

			sprintf(usart_buffer, "%u\r\n", distance);
			USART0_print(usart_buffer);
		}
	}

	return 0;
}

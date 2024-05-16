#include <stdio.h>
#include <stdbool.h>

#include <util/delay.h>

#include "usart.h"
#include "timers.h"
#include "leds.h"
#include "adc.h"

#define BAUD_RATE 9600

extern volatile uint16_t millis;
bool light_low = false;

int main()
{
	// Initialize USART
	USART0_init(CALC_USART_UBRR(BAUD_RATE));
	Timer0_init_pwm();
	Timer2_init_1000hz();
	init_bluetooth_conn_led();
	adc_init();

	USART0_print("AT+NAMELEGO-CAR\r\n");
	USART0_print("AT+NLLEGO-CAR\r\n");

	char usart_buffer[30];

	while (1) {
		if (millis >= 1000) {
			millis = 0;
			
			uint16_t result = adc_get_light_value();
			sprintf(usart_buffer, "%u %u\r\n", result, millis);
			USART0_print(usart_buffer);
		}
	}

	return 0;
}

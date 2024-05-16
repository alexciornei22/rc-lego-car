#include <stdio.h>
#include <util/delay.h>

#include "usart.h"
#include "timers.h"
#include "leds.h"

#define BAUD_RATE 9600

int main()
{
	// Initialize USART
	USART0_init(CALC_USART_UBRR(BAUD_RATE));
	Timer0_init_pwm();
	init_bluetooth_conn_led();
	
	USART0_print("AT+NAMELEGO-CAR\r\n");
	USART0_print("AT+NLLEGO-CAR\r\n");

	char usart_buffer[30];

	while (1) {
		_delay_ms(200);

		if (OCR0A + 10 < 255) {
			OCR0A += 10;
		} else {
			OCR0A = 0;
		}
		
		if (UCSR0A & _BV(RXC0)) {
			USART0_receive_until_newline(usart_buffer);

			PORTC ^= _BV(PC3);
		}
	}

	return 0;
}

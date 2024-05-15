#include <stdio.h>
#include <util/delay.h>

#include "usart.h"
#include "timers.h"

#define BAUD_RATE 9600

int main()
{
	// Initialize USART
	USART0_init(CALC_USART_UBRR(BAUD_RATE));
	Timer0_init_pwm();

	USART0_print("AT+NAMELEGO-CAR\r\n");
	USART0_print("AT+NLLEGO-CAR\r\n");

	char buffer[30];

	while (1) {
		_delay_ms(200);

		if (OCR0A + 10 < 255) {
			OCR0A += 10;
		} else {
			OCR0A = 0;
		}
		
		USART0_receive_until_newline(buffer);
		USART0_print(buffer);
	}

	return 0;
}

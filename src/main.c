#include <stdio.h>
#include <util/delay.h>

#include "usart.h"

#define BAUD_RATE 9600

int main()
{
	// Initialize USART
	USART0_init(CALC_USART_UBRR(BAUD_RATE));

	while (1) {

	}

	return 0;
}

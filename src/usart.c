#include <stdio.h>
#include <avr/io.h>

#include "usart.h"

void USART0_init(unsigned int ubrr)
{
    /* baud rate registers */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* enable TX and RX */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    /* frame format: 8 bits, 2 stop, no parity */
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART0_transmit(char data)
{
    /* wait until buffer is empty */
    while (!(UCSR0A & (1<<UDRE0)));

    /* by writing to this register, transmission hardware is triggered */
    UDR0 = data;
}

char USART0_receive()
{
    /* busy wait until reception is complete */
    while (!(UCSR0A & (1<<RXC0)));

    /* the received byte is read from this register */
    return UDR0;
}

void USART0_receive_until_newline(char *buffer)
{
    char c;
    do {
        c = USART0_receive();
        *buffer = c;
        buffer++;
    } while (c != '\n');
    
    *buffer = '\0';
}

void USART0_print(const char *str)
{
    while (*str != '\0') {
        USART0_transmit(*str++);
    }
}

#include <stdio.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart.h"

static volatile char usart_buffer[USART_BUFFER_MAX_LEN];
static volatile size_t usart_buffer_len = 0;
static volatile bool string_received = false;

void USART0_init(unsigned int ubrr)
{
    /* baud rate registers */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* enable TX and RX */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    // enable receive complete interrupt
    UCSR0B |= _BV(RXCIE0);

    /* frame format: 8 bits, 2 stop, no parity */
    UCSR0C = _BV(USBS0) | (3<<UCSZ00);
}

void USART0_transmit(char data)
{
    /* wait until buffer is empty */
    while (!(UCSR0A & (1<<UDRE0)));

    /* by writing to this register, transmission hardware is triggered */
    UDR0 = data;
}

bool USART0_string_received()
{
    return string_received;
}

const char* USART0_read_buffer()
{
    // null terminate the usart buffer string
    usart_buffer[usart_buffer_len] = '\0';
    // reset buffer length
    usart_buffer_len = 0;
    // clear string received flag
    string_received = false;

    return (const char*) usart_buffer;
}

ISR(USART_RX_vect) {
    // read data register into buffer and increase its length
    uint8_t new_data = UDR0;
    usart_buffer[usart_buffer_len++] = new_data;

    // reset buffer length on overflow
    if (usart_buffer_len >= USART_BUFFER_MAX_LEN - 1) {
        usart_buffer_len = 0;
    }

    // set string received flag
    if (new_data == '\n') {
        string_received = true;
    }
}

void USART0_print(const char *str)
{
    while (*str != '\0') {
        USART0_transmit(*str++);
    }
}

void USART0_print_crlf(const char *str)
{
    USART0_print(str);
    USART0_print("\r\n");
}

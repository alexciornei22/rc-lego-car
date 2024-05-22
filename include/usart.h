#ifndef USART_H_
#define USART_H_

#include <stdbool.h>

#define USART_BUFFER_MAX_LEN 64

/** Macro to compute the UBRR register from CPU frequency &
 * desired baud rate */
#define CALC_USART_UBRR(BAUD) (F_CPU / 16 / (BAUD) - 1)

/*
 * Initialize the USART peripheral.
 */
void USART0_init(unsigned int ubrr);

/*
 * Transmit a byte through the USART.
 *
 * @param `data`: the character to send
 */
void USART0_transmit(char data);

/*
 * Returns the value of the string received flag
 */
bool USART0_string_received();

/**
 * Returns a pointer to the start of the receive buffer string,
 * RESETS buffer length to 0,
 * CLEARS string received flag
*/
const char* USART0_read_buffer();

/*
 * Trasmits a null-terminated string through the USART.
 *
 * @param str: the string to send
 */
void USART0_print(const char *str);

/**
 * Trasmits a null-terminated string 
 * appended with "\\r\\n" through the USART.
 *
 * @param str: the string to send
 */
void USART0_print_crlf(const char *str);

#endif // USART_H_

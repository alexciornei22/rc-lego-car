#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

/**
 * Commands for bluetooth module initialization
*/
void bluetooth_init();

/**
 * Handle command received through USART from
 * bluetooth module
*/
void handle_bluetooth_command(char* command);

#endif // BLUETOOTH_H_

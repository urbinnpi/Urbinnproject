/*
* USART.h
*
* Created: 21-9-2017 10:56:00
* Author: lucan
*/

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdlib.h> // for itoa
#include <util/delay.h>
#include "../CAN/Canbus.h"

#define DEBUG_USART(message) print_string_new_line(message)

#define UART_RECEIVE_BUFFER_MAX_SIZE 40
#define UART_BAUDRATE 115200	// define the baudrate of the serial communication

void UART_init(uint32_t);				// initialize the USART

void print_int(int32_t);				// send an int
void print_int_new_line(int32_t);		// send an int and newline

void print_string(char *);				// send a string
void print_string_new_line(char *);		// send a string and newline

void plot1(uint32_t);					// plot one value in SerialPortPlotter
void plot2(uint32_t, uint32_t);			// plot two values in SerialPortPlotter

void UARTReceiveMessage();

extern volatile char UARTReceiveBuffer[UART_RECEIVE_BUFFER_MAX_SIZE];	// receive buffer
extern volatile uint8_t UARTReceiveBufferCounter;						// counter of the buffer

#endif /* USART_H_ */
/*
* USART.h
*
* Created: 21-9-2017 10:56:00
* Author: lucan
*/

#ifndef USART_H_
#define USART_H_
#define F_CPU 16000000UL // 16MHz

#include <avr/io.h>
#include <stdlib.h> // for itoa
#include <util/delay.h>
#include "../CAN/Canbus.h"

#define DEBUG_USART(message) print_string_new_line(message)
#define RECEIVE_BUFFER_MAX_SIZE 40
#define USART_BAUDRATE 38400	// define the baudrate of the serial communication

void USART_init(uint32_t);				// initialize the USART

void USART_transmit(const char*);		// Function to send one char over the USART

void print_int(int32_t);				// send an int
void print_int_new_line(int32_t);		// send an int and newline

void print_string(char *);				// send a string
void print_string_new_line(char *);		// send a string and newline

void plot1(uint32_t);					// plot one value in SerialPortPlotter
void plot2(uint32_t, uint32_t);			// plot two values in SerialPortPlotter

void print_new_line();					// print a new line

void clearBuffer();

void receive();

extern volatile char receiveBuffer[RECEIVE_BUFFER_MAX_SIZE];	// receive buffer				// send buffer
extern volatile uint8_t receiveBufferCounter;					// counter

#endif /* USART_H_ */
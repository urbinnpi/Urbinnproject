/**
 *
 *
 * Copyright (c) 2008-2009  All rights reserved.
 */

#include <stdint.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>

#include "global.h"
#include "mcp2515.h"
#include "defaults.h"
#include "Canbus.h"
#include "../UART/USART.h"
#include "../stateMachine.h"
#include "../ADC/ADC.h"

volatile tCAN CANUARTReceiveBuffer[CAN_UART_RECEIVE_BUFFER_MAX_SIZE];
volatile uint8_t CANUARTReceiveBufferCounter;


// PD2 (message received interrupt)
ISR(INT0_vect) {
	// check edge
	if(~(PIND & (1 << PIND2))) {
		// set the received frame in the buffer
		mcp2515_get_message((tCAN*)&CANUARTReceiveBuffer[CANUARTReceiveBufferCounter]);
		CANUARTReceiveBufferCounter++;

		// set the state to parse the message
		addState(ST_READ_CAN);
	} else {
		// do nothing
	}
}


void CANReceiveMessage() {
	cli();

	tCAN message;

	// print all the messages in the buffer
	for (; CANUARTReceiveBufferCounter > 0; CANUARTReceiveBufferCounter--) {
		print_string("CAN frame received: ");

		message = CANUARTReceiveBuffer[CANUARTReceiveBufferCounter-1];

		// check for id's maybe we should do something with them.
		if (message.id == 0x700) { // Test 1
			CANPrintMessage(&message);
			return;
		} else if (message.id == 0x704) { // Test 4
			CANPrintMessage(&message);
			return;
		} else if (message.id == 0x705) { // test 5
			print_int_new_line(message.data[0] << 8 | message.data[1]);
			return;
		} else if (message.id == 0x100) { // potmeter reply
			print_int_new_line((uint32_t)(message.data[0] << 8 | message.data[1]));
		}

		// print the message on the screen
		CANPrintMessage(&message);
	}

	sei();
}

void CANPrintMessage(tCAN *message) {
	char hexbuffer[4];		// temp buffer for converting to string

	// print to ID, convert the uint16 to string in HEX format
	print_string("ID: ");
	snprintf(hexbuffer, 6, "0x%02X"PRIu16, message->id);
	print_string(hexbuffer);

	print_string(", ");

	// print the datalength, convert the uint16 to string in HEX format
	print_string("Datalength: ");
	snprintf(hexbuffer, 2, "%X"PRIu16, message->id);
	print_string(hexbuffer);

	// loop and print all the data
	// convert uint8 to string in HEX format
	print_string(", Data: ");
	for(int i=0;i<message->header.length;i++) {
		snprintf(hexbuffer, 3, "%02X"PRIu8, message->data[i]);
		print_string(hexbuffer);
	}
	// print a new line
	print_string_new_line("");
}

void CANTransmitMessage(tCAN *message) {

	mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);

	mcp2515_send_message(message);
}

uint8_t CAN_INIT(unsigned char speed) {
	cli(); // disable interrupts

	// Set PD2 as input
	DDRD &= ~(1<<DDD3);
	PORTD |= (1<<PORTD3);

	// enable interrupt on PD2 (INT0) on the rising edge
	EICRA |= (1 << ISC10) | (1 << ISC11); // any logic

	// enable INT0
	EIMSK |= (1 << INT0);

	sei(); // enable interrupts

	// init the MCP2515
	return mcp2515_init(speed);
}
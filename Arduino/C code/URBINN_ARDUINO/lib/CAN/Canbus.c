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
#include "../common.h"

// PD2 (message received interrupt)
ISR(INT0_vect) {
	//message_rx();
	addState(ST_READ_CAN);
}


char message_rx() {
	tCAN message;

	if (mcp2515_get_message(&message)) {
		char hexbuffer[4];		// temp buffer for converting to string

		// print to ID, convert the uint16 to string in HEX format
		print_string("ID: ");
		snprintf(hexbuffer,4,"%02X"PRIu16,message.id);
		print_string(hexbuffer);

		print_string(", ");

		// print the datalength, convert the uint16 to string in HEX format
		print_string("Datalength: ");
		snprintf(hexbuffer,2,"%02X"PRIu16,message.id);
		print_string(hexbuffer);

		// loop and print all the data
		// convert uint8 to string in HEX format
		print_string(", Data: ");
		for(int i=0;i<message.header.length;i++) {
			snprintf(hexbuffer,3,"%02X"PRIu8,message.data[i]);
			print_string(hexbuffer);
		}
		// print a new line
		print_string_new_line("");
	}
	return 0;
}

char message_tx(tCAN *message) {

	mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);

	if (mcp2515_send_message(message)) {
		//	SET(LED2_HIGH);
		return 1;
	} else {
		return 0;
	}
	return 1;
}

char CAN_INIT(unsigned char speed) {
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
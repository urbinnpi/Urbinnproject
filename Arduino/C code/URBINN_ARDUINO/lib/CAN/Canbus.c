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

// PD2 (message received interrupt)
ISR(INT0_vect) {
	message_rx();
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
}

char message_tx() {
	tCAN message;


	// random init -- need to change this
	message.id = 0x7DF;
	message.header.rtr = 0;
	message.header.length = 8;
	message.data[0] = 0x02;
	message.data[1] = 0x01;
	message.data[2] = 0x05;
	message.data[3] = 0x00;
	message.data[4] = 0x00;
	message.data[5] = 0x00;
	message.data[6] = 0x00;
	message.data[7] = 0x00;

	mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);

	if (mcp2515_send_message(&message)) {
		//	SET(LED2_HIGH);
		return 1;
	} else {
		return 0;
	}
	return 1;
}

char ecu_req(unsigned char pid,  char *buffer)
{
	tCAN message;
	float engine_data;
	int timeout = 0;
	char message_ok = 0;

	// Prepare message
	message.id = PID_REQUEST;
	message.header.rtr = 0;
	message.header.length = 8;
	message.data[0] = 0x02;
	message.data[1] = 0x01;
	message.data[2] = pid;
	message.data[3] = 0x00;
	message.data[4] = 0x00;
	message.data[5] = 0x00;
	message.data[6] = 0x00;
	message.data[7] = 0x00;


	mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);

	if (mcp2515_send_message(&message)) {
	}
				if (mcp2515_check_message())
				{

					if (mcp2515_get_message(&message))
					{
							switch(message.data[2])
								{   /* Details from http://en.wikipedia.org/wiki/OBD-II_PIDs */
									case ENGINE_RPM:  			//   ((A*256)+B)/4    [RPM]
									engine_data =  ((message.data[3]*256) + message.data[4])/4;
									sprintf(buffer,"%d rpm ",(int) engine_data);
									break;

									case ENGINE_COOLANT_TEMP: 	// 	A-40			  [degree C]
									engine_data =  message.data[3] - 40;
									sprintf(buffer,"%d degC",(int) engine_data);
									break;

									case VEHICLE_SPEED: 		// A				  [km]
									engine_data =  message.data[3];
									sprintf(buffer,"%d km ",(int) engine_data);
									break;

									case MAF_SENSOR:   			// ((256*A)+B) / 100  [g/s]
									engine_data =  ((message.data[3]*256) + message.data[4])/100;
									sprintf(buffer,"%d g/s",(int) engine_data);
									break;

									case O2_VOLTAGE:    		// A * 0.005   (B-128) * 100/128 (if B==0xFF, sensor is not used in trim calc)
									engine_data = message.data[3]*0.005;
									sprintf(buffer,"%d V",(int) engine_data);
									break;

									case THROTTLE:				// Throttle Position
									engine_data = (message.data[3]*100)/255;
									sprintf(buffer,"%d %% ",(int) engine_data);
									break;

								}
					}
				}

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

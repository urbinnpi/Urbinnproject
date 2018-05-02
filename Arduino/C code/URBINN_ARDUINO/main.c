/*
 * URBINN_ARDUINO.c
 *
 * Created: 25-4-2018 14:46:07
 * Author : Lucan de Groot
 */
#define F_CPU 16000000UL //16Mhz

#include "lib/UART/USART.h"
#include "lib/CAN/Canbus.h"
#include "lib/CAN/defaults.h"
#include "lib/CAN/global.h"
#include "lib/CAN/mcp2515.h"

#include <stdio.h>

int main() {
	// start the serial connection with the PC
	USART_init(USART_BAUDRATE);

	// start the CAN connection
	if (CAN_INIT(CANSPEED_500)){
		DEBUG_USART("CAN init succes");
	} else {
		DEBUG_USART("CAN init failed");
	}

	DEBUG_USART("Starting main loop...");
	tCAN message;	// create an empty message
	while (1) { // our main event loop
		//  check if there is an message
		if (mcp2515_check_message()) {
			// Get the message from the MCP2515
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
	}
}


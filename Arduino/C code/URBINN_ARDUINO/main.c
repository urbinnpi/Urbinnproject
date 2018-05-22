/*
 * URBINN_ARDUINO.c
 *
 * Created: 25-4-2018 14:46:07
 * Author : Lucan de Groot
 */
#define F_CPU 16000000UL //16Mhz

#include <util/delay.h>
#include <stdio.h>

#include "lib/common.h"
#include "lib/CAN/Canbus.h"
#include "lib/SPI/SPI.h"
#include "lib/UART/USART.h"


// start in the init state
volatile state state_queue[STATE_QUEUE_SIZE] = {0};

int main() {
	init_system();

	while(1) {
		// get the latest state
		state current_state = state_queue[0];

		print_string_new_line((char*)&state_queue);

		// state machine off all the possible states
		switch(current_state){

			case ST_READ_UART:
				// received data from the CAN
				message_rx();
				done();
				DEBUG_USART("Read UART state done!");
			break;

			case ST_READ_CAN:
				// received data from the CAN
				receive();
				done();
				DEBUG_USART("Read CAN state done!");
			break;

			default:
				// Nothing to do!
				DEBUG_USART("Nothing to do!");
			break;
		}
	}
}


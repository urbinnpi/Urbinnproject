/*
 * URBINN_ARDUINO.c
 *
 * Created: 25-4-2018 14:46:07
 * Author : Lucan de Groot
 */
#include <util/delay.h>
#include <stdio.h>

#include "lib/stateMachine.h"
#include "lib/CAN/Canbus.h"
#include "lib/SPI/SPI.h"
#include "lib/UART/USART.h"


// declare the state_queue and make sure it's all zero
volatile state_t state_queue[STATE_QUEUE_SIZE] = {0};

int main() {
	init_system();

	while(1) {
		// get the latest state
		state_t current_state = state_queue[0];

		// state machine off all the possible states
		switch(current_state) {

			case ST_READ_UART:
				// received data from the UART
				UARTReceiveMessage();
				done();
				break;

			case ST_READ_CAN:
				// received data from the CAN
				CANReceiveMessage();
				done();
				break;

			default:
				// Nothing to do!
				// Maybe poll sensors that don't interrupt
				break;
		}
	}
}


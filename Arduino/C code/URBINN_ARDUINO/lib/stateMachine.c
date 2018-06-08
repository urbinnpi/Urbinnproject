/*
 * stateMachine.c
 *
 * Created: 22-5-2018 11:43:58
 *  Author: lucan
 */

#include "SPI/SPI.h"
#include "UART/USART.h"
#include "CAN/Canbus.h"
#include "stateMachine.h"
#include <avr/interrupt.h>
#include <string.h> // for memset

static volatile uint8_t state_index = 0;

void init_system() {
	// start the serial connection with the PC
	UART_init(UART_BAUDRATE);

	// start the spi connection with the MCP2515
	spi_init_master();

	// start the CAN connection
	if (CAN_INIT(CANSPEED_500)){
		DEBUG_USART("CAN init succes");
	} else {
		DEBUG_USART("CAN init failed");
	}
	// enable interrupts
	sei();
}

// done with the first state, move everything over one.
void done() {
	// disable interrupts, so the array can't be changed during this function
	cli();

	// go through the array and move everything over one
	uint8_t i;
	for (i = 0; i < STATE_QUEUE_SIZE; i++) {
		state_queue[i] = state_queue[i+1];
	}
	// set the last state manually back to 0
	state_queue[i+1] = 0;

	// if the index is not 0, move it one back
	if(state_index){
		state_index--;
	}

	// enable interrupts again
	sei();
}

// add a state and increment the index
void addState(state_t s) {
	cli();

	// check if the queue is full
	if(state_index >= STATE_QUEUE_SIZE) {
		print_string_new_line("Queue full!!");
		return;
	}

	// add the state
	state_queue[state_index] = s;
	state_index++;

	sei();
}

void clearQueue() {
	cli();

	memset((state_t*)state_queue, ST_IDLE, STATE_QUEUE_SIZE); // clear the array
	state_index = 0;	// reset the index

	sei();
}
/*
 * stateMachine.c
 *
 * Created: 22-5-2018 11:43:58
 *  Author: lucan
 */

#include "SPI/SPI.h"
#include "UART/USART.h"
#include "CAN/Canbus.h"
#include "ADC/ADC.h"
#include "stateMachine.h"
#include "TIMER/TIMER.h"
#include <avr/interrupt.h>
#include <string.h> // for memset

static volatile uint8_t state_index = 0;
static void clearQueue();

/**
 *	 This function inits the system, put all init functions here
 */
void init_system() {
	// start the serial connection with the PC
	UART_init(UART_BAUDRATE);

	// start the spi connection with the MCP2515
	spi_init_master();

	// start the adc
	init_ADC();

	// start the timer
	TIMER_init();

	// start the watchdog
	WatchDog_init();

	// start the CAN connection
	if (CAN_INIT(CANSPEED_500)){
		DEBUG_USART("CAN init succes");
	} else {
		DEBUG_USART("CAN init failed");
	}
	// enable interrupts
	sei();

	print_string_new_line("System init done");
}

/**
 *	This function clears the active state, and sets the next one
 */
void done() {
	
	// move the array over by one
	memmove(&state_queue[0], &state_queue[1], STATE_QUEUE_SIZE-1);
	
	// set the last index to 0
	state_queue[STATE_QUEUE_SIZE-1] = ST_IDLE;

	// if the index is not 0, move it one back
	if(state_index){
		state_index--;
	}
}

/**
 *	This function adds a state to the queue
 */
void addState(state_t s) {
	// check if the queue is full
	if(state_index >= STATE_QUEUE_SIZE) {
		cli();
		print_string_new_line("Queue full!!");
		
		// reset the system by overflowing the watchdog timer 
		clearQueue();
		_delay_ms(1000);
		sei();
		return;
	}

	// add the state
	state_queue[state_index] = s;
	state_index++;
}

/**
 * This function clears the queue
 */
void clearQueue() {
	memset((state_t*)state_queue, ST_IDLE, STATE_QUEUE_SIZE); // clear the array
	state_index = 0;	// reset the index
}
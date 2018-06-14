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
#include "lib/ADC/ADC.h"
#include "lib/TIMER/TIMER.h"


// declare the state_queue and make sure it's all zero
volatile state_t state_queue[STATE_QUEUE_SIZE] = {0};

int main() {
	
	// start the system
	init_system();

	while(1) {
		// Reset the watchdog timer 
		WatchDog_reset();

		// get the latest state
		state_t current_state = state_queue[0];

		// state machine off all the possible states
		switch(current_state) {
			case ST_IDLE:
				// Do nothing
				break;
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

			case ST_ADC_DONE:
				// adc is done and send the data over CAN
				ADCSendMessage();
				done();
				break;
			
			case ST_POLL_SENSOR:
				// stop the timer
				stopTimer();
				
				// poll all sensors
				read_ADC(0);
				
				done();
				
				// Start the timer again
				TIMERReInit();
				break;

			default:
				// Nothing to do!
				break;
		}
	}
}


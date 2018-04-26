/*
 * URBINN_ARDUINO.c
 *
 * Created: 25-4-2018 14:46:07
 * Author : Lucan de Groot
 */
#define F_CPU 16000000UL //16Mhz

#include "lib/UART/USART.h"
#include "lib/CAN/Canbus.h"


int main() {
	// start the serial connection with the PC
	USART_init(USART_BAUDRATE);

	// start the CAN connection
	if (CAN_INIT(CANSPEED_500)){
		//DEBUG_USART("CAN init succes");
	} else {
		//DEBUG_USART("CAN init failed");
	}

	while (1) { // our main event loop
		//DEBUG_USART("test12345");
		print_string_new_line("test12345");
	}
}


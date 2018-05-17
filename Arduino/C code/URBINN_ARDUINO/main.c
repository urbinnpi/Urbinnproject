/*
 * URBINN_ARDUINO.c
 *
 * Created: 25-4-2018 14:46:07
 * Author : Lucan de Groot
 */
#define F_CPU 16000000UL //16Mhz

#include <util/delay.h>

#include "lib/SPI/SPI.h"
#include "lib/UART/USART.h"
#include "lib/CAN/Canbus.h"
#include "lib/CAN/defaults.h"
#include "lib/CAN/global.h"
#include "lib/CAN/mcp2515.h"

#include <stdio.h>

int main() {
	// start the serial connection with the PC
	USART_init(USART_BAUDRATE);

	spi_init_master();

	// start the CAN connection
	if (CAN_INIT(CANSPEED_500)){
		DEBUG_USART("CAN init succes");
	} else {
		DEBUG_USART("CAN init failed");
		return 1;
	}

	DEBUG_USART("Starting main loop...");
	while (1) { // our main event loop
		if (messageReceived) {
			receive();
			messageReceived = False;
		}
	}
}


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
	tCAN message;
	while (1) { // our main event loop
		message.id = 0x631; //formatted in HEX
		message.header.rtr = 0;
		message.header.length = 8; //formatted in DEC
		message.data[0] = 0x40;
		message.data[1] = 0x05;
		message.data[2] = 0x30;
		message.data[3] = 0xFF; //formatted in HEX
		message.data[4] = 0x00;
		message.data[5] = 0x40;
		message.data[6] = 0x00;
		message.data[7] = 0x00;

		message_tx(&message);
		_delay_ms(100);
	}
}


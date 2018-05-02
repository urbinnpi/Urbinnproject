/*
 * URBINN_ARDUINO.c
 *
 * Created: 25-4-2018 14:46:07
 * Author : Lucan de Groot
 */
#define F_CPU 16000000UL //16Mhz

#include <util/delay.h>

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
	tCAN message;
	while (1) { // our main event loop
		message.id = 0x001;
		message.header.rtr = 0;
		message.header.length = 4;
		*message.data = 0xAABBCCDD;
		message_tx(&message);
		_delay_ms(100);
	}
}


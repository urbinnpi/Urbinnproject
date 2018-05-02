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
	while (1) { // our main event loop
		tCAN message;
		if (mcp2515_check_message()) {
			if (mcp2515_get_message(&message)) {

				DEBUG_USART("ID: ");
				DEBUG_USART(message.id);
				DEBUG_USART(", ");
				DEBUG_USART("Data: ");
				DEBUG_USART(message.header.length);
				for(int i=0;i<message.header.length;i++) {
					DEBUG_USART(message.data[i]);
					DEBUG_USART(" ");
				}
				DEBUG_USART("");
			}

		}
	}
}


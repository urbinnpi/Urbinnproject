#ifndef canbus__h
#define canbus__h

#include "mcp2515.h"

#define CAN_UART_RECEIVE_BUFFER_MAX_SIZE 10 // max can frames in buffer

#define CANSPEED_125 	7		// CAN speed at 125 kbps
#define CANSPEED_250  	3		// CAN speed at 250 kbps
#define CANSPEED_500	1		// CAN speed at 500 kbps

#define CAN_MAX_LENGTH 8 // can data bits

#define ENGINE_COOLANT_TEMP 0x05
#define ENGINE_RPM          0x0C
#define VEHICLE_SPEED       0x0D
#define MAF_SENSOR          0x10
#define O2_VOLTAGE          0x14
#define THROTTLE			0x11

#define PID_REQUEST         0x7DF
#define PID_REPLY			0x7E8

uint8_t CAN_INIT(unsigned char);
void CANTransmitMessage(tCAN*);
void CANReceiveMessage();

extern volatile tCAN CANUARTReceiveBuffer[CAN_UART_RECEIVE_BUFFER_MAX_SIZE];
extern volatile uint8_t CANUARTReceiveBufferCounter;

#endif

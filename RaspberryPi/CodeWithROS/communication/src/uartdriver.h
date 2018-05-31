#ifndef UARTDRIVER_H
#define UARTDRIVER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include "driver.h"
#include "communication/msgstruct.h"

class UARTparser;

class UARTdriver : public Driver
{
public:
	UARTdriver();
	void readInput(); // Reads CAN shield
	void receiveMsg(communication::msgStruct* msg); // Callback of ROS topic ControllerDriver1
	void transmit(communication::msgStruct* msg); // Writes to CAN shield
	static int s; // Tijdelijk
private:
	//int s; // Socket
};

#endif // UARTDRIVER_H
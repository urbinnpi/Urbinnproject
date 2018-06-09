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

class UARTparser;

class UARTdriver : public Driver
{
public:
	UARTdriver();
	void readInput(); // Reads CAN shield
	void receiveMsg(const communication::msgStruct& msg); // Callback of ROS topic ControllerDriver1
	void transmit(const communication::msgStruct msg); // Writes to CAN shield
	static int s; // Tijdelijk
};

#endif // UARTDRIVER_H
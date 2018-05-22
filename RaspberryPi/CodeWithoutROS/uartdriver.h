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
//#include "uartparser.h"

class UARTparser;

class UARTdriver : public Driver
{
public:
	UARTdriver();
	~UARTdriver();
	void readInput(struct can_frame *frame); // Reads input of CAN shield
	void receiveMsg(struct can_frame *frame); // Callback of ROS topic ControllerDriver1
	void transmit(struct can_frame *frame); // Writes to CAN shield
private:
	int s; // Socket
	UARTparser* up1; // Tijdelijk! Niet nodig met ROS!
};

#endif // UARTDRIVER_H
#ifndef UARTDRIVER_H
#define UARTDRIVER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <iostream>
#include "socketcan/can.h"
#include "driver.h"
#include "uartparser.h"

class UARTdriver : public Driver
{
public:
	UARTdriver();
	~UARTdriver() { delete p; } // Tijdelijk!
	void readInput(struct can_frame *frame); // Reads input of CAN shield
	void receiveMsg(); // Callback of ROS topic ControllerDriver1
	void transmit(struct can_frame *frame); // Writes to CAN shield
private:
	int s; // Socket
	UARTparser* p; // Tijdelijk! Niet nodig met ROS!
	Controller* c; // Tijdelijk! Niet nodig met ROS!
};

#endif // UARTDRIVER_H
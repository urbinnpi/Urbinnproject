#ifndef UARTDRIVER_H
#define UARTDRIVER_H

#include "driver.h"

class UARTdriver : public Driver
{
public:
	UARTdriver();
	void readInput(struct can_frame *frame);
	void receiveMsg();
	void transmit(struct can_frame *frame);
private:
	int s; // Socket
};

#endif // UARTDRIVER_H
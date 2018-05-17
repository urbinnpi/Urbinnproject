#ifndef UARTDRIVER_H
#define UARTDRIVER_H

#include "driver.h"
#include <linux-can-utils>

class UARTdriver : public Driver
{
public:
    UARTdriver();
    void readInput(struct can_frame *frame, int socket);
    void receiveMsg();
    void transmit(struct can_frame *frame, int socket);
private:
	int s;
}

#endif // UARTDRIVER_H
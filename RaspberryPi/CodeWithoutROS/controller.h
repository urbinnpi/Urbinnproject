#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include "definitions.h"

class UARTdriver;

class Controller
{
public:
	//Controller();
	//~Controller();
	void receiveInfo(struct infoStruct *infoFrame);//can_frame *frame); // Callback met infoStruct van topic ParserController1
private:
	void transmitMsg(struct can_frame *frame); // Publish een infoStruct op topic ControllerDriver1
	// void steer, enz.
	//UARTdriver* ud1;
};

#endif // CONTROLLER_H
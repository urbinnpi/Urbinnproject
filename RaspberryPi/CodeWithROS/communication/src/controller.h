#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include <communication/msgStruct.h>
#include <communication/infoStruct.h>

static ros::Subscriber sub;
static ros::Publisher pub;

class UARTdriver;

class Controller
{
public:
	void receiveInfo(communication::infoStruct* info); // Callback met infoStruct van topic ParserController1
private:
	void transmitMsg(communication::msgStruct* msg); // Publish een msgStruct op topic ControllerDriver1
	// void steer, enz.
};

#endif // CONTROLLER_H
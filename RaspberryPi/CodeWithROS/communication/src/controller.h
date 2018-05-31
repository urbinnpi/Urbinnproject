#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include "ros/ros.h"
#include "communication/msgStruct.h"
#include "communication/infoStruct.h"

class UARTdriver;

class Controller
{
public:
	Controller();
	void receiveInfo(const communication::infoStruct& info); // Callback met infoStruct van topic ParserController1
private:
	void transmitMsg(communication::msgStruct msg); // Publish een msgStruct op topic ControllerDriver1
	// void steer, enz.
	ros::NodeHandle nh;
	ros::Publisher pub;
	ros::Subscriber sub;
};

#endif // CONTROLLER_H
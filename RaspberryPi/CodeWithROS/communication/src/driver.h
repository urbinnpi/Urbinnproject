#ifndef DRIVER_H
#define DRIVER_H

#include "ros/ros.h"
#include "communication/msgStruct.h"

static ros::Subscriber sub;
static ros::Publisher pub;

class Driver
{
public:
	virtual ~Driver() {}
    virtual void readInput() = 0;
    virtual void receiveMsg(communication::msgStruct* msg) = 0;
    virtual void transmit(communication::msgStruct* msg) = 0;
};

#endif // DRIVER_H
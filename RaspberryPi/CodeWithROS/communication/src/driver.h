#ifndef DRIVER_H
#define DRIVER_H

#include "communication/msgStruct.h"

class Driver
{
public:
	virtual ~Driver() {}
    virtual void readInput() = 0;
    virtual void receiveMsg(const communication::msgStruct& msg) = 0;
    virtual void transmit(const communication::msgStruct msg) = 0;
};

#endif // DRIVER_H
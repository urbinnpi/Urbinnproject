#ifndef DRIVER_H
#define DRIVER_H

#include "communication/msgstruct.h"

class Driver
{
public:
	virtual ~Driver() {}
    virtual void readInput() = 0;
    virtual void receiveMsg(communication::msgStruct* msg) = 0;
    virtual void transmit(communication::msgStruct* msg) = 0;
};

#endif // DRIVER_H
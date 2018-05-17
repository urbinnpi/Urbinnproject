#ifndef DRIVER_H
#define DRIVER_H

class Driver
{
public:
	virtual ~Driver() {}
    virtual void readInput()=0;//struct can_frame *frame) = 0;
    virtual void receiveMsg() = 0;
    virtual void transmit()=0;//struct can_frame *frame) = 0;
};

#endif // DRIVER_H
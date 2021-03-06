#ifndef DRIVER_H
#define DRIVER_H

class Driver
{
public:
	virtual ~Driver() {}
    virtual void readInput(struct can_frame *frame) = 0;
    virtual void receiveMsg(struct can_frame *frame) = 0;
    virtual void transmit(struct can_frame *frame) = 0;
};

#endif // DRIVER_H
#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include <communication/msgstruct.h>
#include <communication/infostruct.h>

static ros::Subscriber sub;
static ros::Publisher pub;

class Parser
{
public:
	virtual ~Parser() {}
	virtual void parseData(communication::msgStruct* msg) = 0;
private:
	virtual void transmitInfo(communication::infoStruct* info) = 0;
};

#endif // PARSER_H
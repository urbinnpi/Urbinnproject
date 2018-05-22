#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"

class Parser
{
public:
	virtual ~Parser() {}
	virtual void parseData(struct can_frame*) = 0;
private:
	virtual void transmitInfo() = 0;
};

#endif // PARSER_H
#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include "communication/msgStruct.h"
#include "communication/infoStruct.h"

class Parser
{
public:
	virtual ~Parser() {}
	virtual void parseData(const communication::msgStruct msg) = 0;
private:
	virtual void transmitInfo(communication::infoStruct info) = 0;
};

#endif // PARSER_H
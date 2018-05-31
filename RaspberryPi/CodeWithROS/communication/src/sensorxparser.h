#ifndef SENSORXPARSER_H
#define SENSORXPARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <map>
#include "socketcan/can.h"
#include "parser.h"
#include "communication/msgStruct.h"
#include "communication/infoStruct.h"

class Controller;

class SensorXparser : public Parser
{
public:
	void parseData(communication::msgStruct msg);
private:
	void transmitInfo(communication::infoStruct info);
};

#endif // SENSORXPARSER_H
#ifndef SENSORXPARSER_H
#define SENSORXPARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "socketcan/can.h"
#include "parser.h"

class Controller;

class SensorXparser : public Parser
{
public:
	SensorXparser(Controller* c1);
	void parseData(struct can_frame *frame); // Wordt aangeroepen door receiveMsg()
private:
	void transmitInfo(struct can_frame *frame); // Publisht infostructs op topic ParserController1
	Controller* c1;
};

#endif // SENSORXPARSER_H
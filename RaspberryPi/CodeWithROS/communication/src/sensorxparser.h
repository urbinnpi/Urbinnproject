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
#include "ros/ros.h"
#include "communication/msgStruct.h"
#include "communication/infoStruct.h"

class SensorXparser : public Parser
{
public:
	SensorXparser(ros::Publisher* pub);
	void parseData(const communication::msgStruct msg);
private:
	void transmitInfo(communication::infoStruct info);
	ros::Publisher* pub;
};

#endif // SENSORXPARSER_H
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
	SensorXparser(ros::Publisher* pub) : pub(pub) { ROS_INFO("started SensorXparser"); }
	void parseData(const communication::msgStruct msg) { 
		// Translate data from msgStruct to usable data in an infoStruct
		ROS_INFO("SensorXparser got frame to parse");
		communication::infoStruct info;
		info.id = msg.id;
		info.dl = msg.dl;
		for(uint8_t i = 0; info.dl > i; i++) {
			info.data[i] = msg.data[i];
			ROS_INFO("Data of infostruct: %X", info.data[i]);
		}

		ROS_INFO("SensorXparser sending info to controller");

		this->transmitInfo(info);
	}
private:
	void transmitInfo(communication::infoStruct info) {
		pub->publish(info);
	}
	ros::Publisher* pub;
};

#endif // SENSORXPARSER_H
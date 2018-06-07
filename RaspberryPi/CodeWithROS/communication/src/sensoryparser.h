#ifndef SENSORYPARSER_H
#define SENSORYPARSER_H

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

class SensorYparser : public Parser
{
public:
	SensorYparser(ros::Publisher* pub) : pub(pub) { ROS_INFO("started SensorYparser"); }
	void parseData(const communication::msgStruct msg) { 
		// Translate data from msgStruct to usable data in an infoStruct
		ROS_INFO("SensorYparser got frame to parse");
		communication::infoStruct info;
		info.id = msg.id;
		info.dl = msg.dl;
		for(uint8_t i = 0; info.dl > i; i++) {
			info.data[i] = msg.data[i];
		}
		ROS_INFO("SensorYparser sending info to controller");

		this->transmitInfo(info);
	}
private:
	void transmitInfo(communication::infoStruct info) {
		pub->publish(info);
	}
	ros::Publisher* pub;
};

#endif // SENSORYPARSER_H
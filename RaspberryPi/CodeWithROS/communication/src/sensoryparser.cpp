#include "sensoryparser.h"

SensorYparser::SensorYparser(ros::Publisher* pub) : pub(pub) {
	ROS_INFO("started SensorYparser");
}

void SensorYparser::parseData(const communication::msgStruct msg) {
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

void SensorYparser::transmitInfo(communication::infoStruct info) {
	pub->publish(info);
}

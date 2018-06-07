#include "sensorxparser.h"

SensorXparser::SensorXparser(ros::Publisher* pub) : pub(pub) {
	ROS_INFO("started SensorXparser");
}

void SensorXparser::parseData(const communication::msgStruct msg) {
	// Translate data from msgStruct to usable data in an infoStruct
	ROS_INFO("SensorXparser got frame to parse");
	communication::infoStruct info;
	info.id = msg.id;
	info.dl = msg.dl;
	for(uint8_t i = 0; info.dl > i; i++) {
		info.data[i] = msg.data[i];
	}
	ROS_INFO("SensorXparser sending info to controller");

	this->transmitInfo(info);
}

void SensorXparser::transmitInfo(communication::infoStruct info) {
	pub->publish(info);
}

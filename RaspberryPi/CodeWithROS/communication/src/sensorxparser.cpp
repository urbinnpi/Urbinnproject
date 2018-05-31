#include "sensorxparser.h"
#include "uartparser.h"

void SensorXparser::parseData(communication::msgStruct* msg) {
	// Translate data from msgStruct to usable data in an infoStruct
	/*struct infoStruct infoFrame;
	infoFrame.id = frame->can_id;
	infoFrame.dl = frame->can_dlc;
	for(uint8_t i = 0; frame->can_dlc > i; i++) {
		infoFrame.data[i] = frame->data[i];
	}
	this->transmitInfo(&infoFrame);*/
	this->transmitInfo(msg);
}

void SensorXparser::transmitInfo(communication::infoStruct* info) {
	pub.publish(&info);
}

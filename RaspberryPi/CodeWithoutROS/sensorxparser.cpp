#include "sensorxparser.h"
#include "controller.h"

SensorXparser::SensorXparser() : c1(new Controller()) {

}

SensorXparser::~SensorXparser() {
	delete c1;
}

void SensorXparser::parseData(struct can_frame *frame)
{
	// Vertaal data van msgStruct naar bruikbare data in een infoStruct
	/*struct infoStruct infoFrame;
	infoFrame.id = frame->can_id;
	infoFrame.dl = frame->can_dlc;
	for(uint8_t i = 0; frame->can_dlc > i; i++) {
		infoFrame.data[i] = frame->data[i];
	}
	this->transmitInfo(&infoFrame);*/
	this->transmitInfo(frame);
}

void SensorXparser::transmitInfo(struct can_frame *frame)
{
	// Bij gebruik ROS hier infoStruct publishen op topic ParserController1
	c1->receiveInfo(frame); // Tijdelijk gebruik van controller callback
}

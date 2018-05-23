#include "sensorxparser.h"
#include "controller.h"

SensorXparser::SensorXparser() : c1(new Controller()) {

}

SensorXparser::~SensorXparser() {
	delete c1;
}

void SensorXparser::parseData(struct can_frame *frame)
{
	// Haal nuttige info uit frame
	struct infoStruct infoFrame;
	infoFrame.id = frame->can_id;
	infoFrame.dl = frame->can_dlc;
	//infoFrame.data = frame->data;
	for(uint8_t i = 0; frame->can_dlc > i; i++) {
		infoFrame.data[i] = frame->data[i];
	}
	// voer transmitInfo uit met nuttige info in infostruct
	//this->transmitInfo(frame);
	this->transmitInfo(&infoFrame);
}

void SensorXparser::transmitInfo(struct infoStruct *infoFrame)//can_frame *frame)
{
	// Bij gebruik ROS hier infostruct publishen op topic ParserController1
	//c1->receiveInfo(frame); // Tijdelijk gebruik van controller callback
	c1->receiveInfo(infoFrame);
}

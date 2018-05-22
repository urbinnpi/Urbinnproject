#include "sensorxparser.h"
#include "controller.h"

SensorXparser::SensorXparser() : c(new Controller()) {

}

SensorXparser::~SensorXparser() {
	delete c;
}

void SensorXparser::parseData(struct can_frame *frame)
{
	// Haal nuttige info uit frame
	// voer transmitInfo uit met nuttige info in infostruct
	this->transmitInfo(frame);
}

void SensorXparser::transmitInfo(struct can_frame *frame)
{
	// Bij gebruik ROS hier infostruct publishen op topic ParserController1
	c->receiveInfo(frame); // Tijdelijk gebruik van controller callback
}
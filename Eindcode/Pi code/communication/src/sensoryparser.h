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

#define ADC_TO_DEGREES_SLOPE 1.0 * (180.0 / 1023.0)

class SensorYparser : public Parser
{
public:
	SensorYparser(ros::Publisher* pub) : pub(pub) { ROS_INFO("started SensorYparser"); }
	void parseData(const communication::msgStruct msg) { 
		// Translate data from msgStruct to usable data in an infoStruct
		//ROS_INFO("SensorYparser got frame to parse");
		communication::infoStruct info;
		info.id = msg.id;
		
		uint16_t adcReading = msg.data[0] << 8 | msg.data[1];
		
		// set to degrees 0 - 180
		uint8_t degrees = ADC_TO_DEGREES_SLOPE * adcReading;
		
		ROS_INFO("ADC value potmeter: %i", adcReading);
		ROS_INFO("Potmeter degrees: %i", degrees);
		
		// set the degrees into the data array
		info.data[0] = degrees;
		info.dl = 1; // length is one
		
		
		//ROS_INFO("SensorYparser sending info to controller");

		this->transmitInfo(info);
	}
private:
	void transmitInfo(communication::infoStruct info) {
		pub->publish(info);
	}
	ros::Publisher* pub;
};

#endif // SENSORYPARSER_H
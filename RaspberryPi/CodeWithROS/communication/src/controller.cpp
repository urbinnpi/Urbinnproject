//#include <iostream>
//#include <string>
#include "controller.h"
#include "uartdriver.h"
#include "idlist.h"

//std::hex decToHex(int dec);
//std::hex strToHex(std::string str);

Controller::Controller() {
	pub = nh.advertise<communication::msgStruct>("controllerdriver1", 1000);
	sub = nh.subscribe("parsercontroller1", 1000, &Controller::receiveInfo, this);
	
	ROS_INFO("Started Controller");
}

void Controller::receiveInfo(const communication::infoStruct& info) { // Callback of topic parsercontroller1
	// Lees infostruct uit en voer aan de hand daarvan functies zoals steer of brake uit
	// Deze functies kunnen vervolgens messages sturen naar de driver met transmitMsg()
	
	ROS_INFO("Controller got info, sending commandos");	
	
	// ----- WERKEND - ZELFDE TERUGSTUREN ALS ONTVANGEN ----- //
	/*communication::msgStruct msg;
	msg.id = info.id;
	msg.dl = info.dl;
	for(uint8_t i = 0; msg.dl > i; i++) {
		msg.data[i] = info.data[i];
		ROS_INFO("Commando data: %X", msg.data[i]);
	}*/
	// ------------------------------------------------------ //

	if(info.id == SensorXid) {
		if((info.data[0] == 0x61)
			&& (info.data[1] == 0x61))
		{
			communication::msgStruct msg;
			msg.id = 0x100;
			msg.dl = 2;
			for(uint8_t i = 0; msg.dl > i; i++) {
				msg.data[0] = 0x61; // ASCII: a
				msg.data[1] = 0x62; // ASCII: b
			}
		}
		this->transmitMsg(msg);
	}

	// ---------- TEST - GEBRUIK TOHEX FUNCTIES ---------- //
	/*if((info.id == SensorXid)
		&& (info.data[0] == strToHex("a"))
		&& (info.data[1] == strToHex("a")))
	{
		communication::msgStruct msg;
		msg.id = 0x100;
		msg.dl = 2;
		for(uint8_t i = 0; msg.dl > i; i++) {
			msg.data[0] = 0x61; // ASCII: a
			msg.data[1] = 0x62; // ASCII: b
		}
	}*/
	// --------------------------------------------------- //

	// ---------- TEST - SENSORDATA VERGELIJKEN ---------- //
	/*if((info.id == SensorXid)
		&& (info.data[0] + info.data[1] == decToHex(100))
	{
		communication::msgStruct msg;
		msg.id = 0x100;
		msg.dl = 2;
		for(uint8_t i = 0; msg.dl > i; i++) {
			msg.data[0] = 0x61; // ASCII: a
			msg.data[1] = 0x62; // ASCII: b
		}
	}*/
	// --------------------------------------------------- //
}

void Controller::transmitMsg(communication::msgStruct msg) {
	ROS_INFO("Controller sending commando");
	pub.publish(msg);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "controller"); // Initialize ROS node with name controller
	Controller c1;
	ros::Rate loop_rate(10); // Set speed of while(ros::ok()) loop, 10 Hz at the moment

	while(ros::ok()) {
		// Ask user input to simulate signals from the Raspberry Pi to Arduino

		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)
	}

	return 0;
}

/*std::hex decToHex(int dec) {
	std::hex value = std::hex << dec;
	return value;
}

std::hex strToHex(std::string str) {
	const char* const lut = "0123456789ABCDEF";
    size_t len = str.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i) {
        const unsigned char c = str[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}*/

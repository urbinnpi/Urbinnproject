#include "controller.h"
#include "uartdriver.h"
#include "idlist.h"

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
	// --- WERKEND - AB TERUGSTUREN BIJ AA VAN SENSORXID ---- //
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
			this->transmitMsg(msg);
		}
	}
	// ------------------------------------------------------ //
	// ------------------- TEST - POTMETER ------------------ //
	if(info.id == SensorYid) {
		ROS_INFO("Potmeter detected");
		
		// get the value 0 - 1023
		uint16_t value = (data[0] << 8) | (data[1]);
		
		// if above threshold
		if(value > 512) {
			communication::msgStruct msg;
			msg.id = 0x100;
			msg.dl = 2;
			for(uint8_t i = 0; msg.dl > i; i++) {
				msg.data[0] = 0x61; // ASCII: a
				msg.data[1] = 0x62; // ASCII: b
			}
			this->transmitMsg(msg);
		}
	}
	// ------------------------------------------------------ //
	// ---------- TEST - GEBRUIK TOHEX FUNCTIES ---------- //
	/*if((info.id == SensorXid)
		&& (info.data[0] == decToHex())
		&& (info.data[1] == decToHex()))
	{
		communication::msgStruct msg;
		msg.id = 0x100;
		msg.dl = 2;
		for(uint8_t i = 0; msg.dl > i; i++) {
			msg.data[0] = 0x61; // ASCII: a
			msg.data[1] = 0x62; // ASCII: b
		}
	}*/
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
		// Transmit control signals (every 10 Hz)
		communication::msgStruct msg; // TEST vv
		msg.id = 0x100;
		msg.dl = 2;
		for(uint8_t i = 0; msg.dl > i; i++) {
			msg.data[0] = 0x61; // ASCII: a
			msg.data[1] = 0x62; // ASCII: b
		}
		c1.transmitMsg(msg); // TEST ^^

		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)
	}

	return 0;
}

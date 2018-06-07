#include "controller.h"
#include "uartdriver.h"
#include "ID.h"

Controller::Controller() {
	pub = nh.advertise<communication::msgStruct>("controllerdriver1", 1000);
	sub = nh.subscribe("parsercontroller1", 1000, &Controller::receiveInfo, this);
	
	ROS_INFO("Started Controller");
}

void Controller::receiveInfo(const communication::infoStruct& info) { // Callback of topic parsercontroller1
	// Lees infostruct uit en voer aan de hand daarvan functies zoals steer of brake uit
	// Deze functies kunnen vervolgens messages sturen naar de driver met transmitMsg()
	
	// print some info about the received data
	ROS_INFO("Controller Got info, sending the data back");
	ROS_INFO("Controller old ID: %x", info.id);	
	
	// create a struct to set the command in
	communication::msgStruct msg;
	
	// see if there is anything to do
	// could be optimized
	switch (info.id) {
		case SensorXID:
			//msg.id = (uint32_t)0x010;
			msg.id = info.id;
			
			// change the data
			for(uint8_t i = 0; msg.dl > i; i++) {
				msg.data[i] = info.data[i];
			}
			
			msg.dl = info.dl; // data length
			
			break;
			
		/*case SensorYID:
			msg.id = 0x020;
			msg.data[1] = 0xFF; // maximum POWER
			msg.dl = 1;
			break;*/
			
		default:
			ROS_WARN("ID %X not found in the controller", info.id);
			
			// exit the function
			return;
			break;
	}
	
	this->transmitMsg(msg);
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
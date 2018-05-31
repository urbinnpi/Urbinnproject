#include "controller.h"
#include "uartdriver.h"

Controller::Controller() {
	pub = nh.advertise<communication::msgStruct>("controllerdriver1", 1000);
	sub = nh.subscribe("parsercontroller1", 1000, &Controller::receiveInfo, this);
}

void Controller::receiveInfo(const communication::infoStruct& info) { // Callback of topic parsercontroller1
	// Lees infostruct uit en voer aan de hand daarvan functies zoals steer of brake uit
	// Deze functies kunnen vervolgens messages sturen naar de driver met transmitMsg()

	/*if(info.id == 0x631) {
		// Voer bijv. functie steer() uit en geef frame mee of zet in buffer

	}*/

	communication::msgStruct msg;
	msg.id = info.id;
	msg.dl = info.dl;
	for(uint8_t i = 0; msg.dl > i; i++) {
		msg.data[i] = info.data[i];
	}
	this->transmitMsg(msg);
}

void Controller::transmitMsg(communication::msgStruct msg) {
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
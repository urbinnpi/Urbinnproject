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
	
	//ROS_INFO("Controller got info, sending commandos");	

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
		//ROS_INFO("Potmeter detected");
		
		communication::msgStruct msg;
		msg.id = 0x100;
		msg.dl = 1;
		
		// copy the degrees
		msg.data[0] = info.data[0];
		
		//ROS_INFO("degrees: %i", info.data[0]);
		
		// check which direction
		if(info.data[0] <= 80) { // Left
			ROS_INFO("Potmeter going left");
			msg.data[0] = 'L';
		} else if (info.data[0] > 80 && info.data[0] < 100) { // forward
			ROS_INFO("Potmeter going forward");
			msg.data[0] = 'F';
		} else if (info.data[0] >= 100) {	// Right
			ROS_INFO("Potmeter going right");
			msg.data[0] = 'R';
		}
		
		// Send the message
		this->transmitMsg(msg);
	}
}

void Controller::transmitMsg(communication::msgStruct msg) {
	//ROS_INFO("Controller sending commando");
	pub.publish(msg);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "controller"); // Initialize ROS node with name controller
	Controller c1;
	ros::Rate loop_rate(10); // Set speed of while(ros::ok()) loop, 10 Hz at the moment

	while(ros::ok()) {
		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)
	}

	return 0;
}

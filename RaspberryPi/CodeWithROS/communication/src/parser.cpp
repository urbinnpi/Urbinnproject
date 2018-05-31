#include "ros/ros.h"
#include "uartparser.h"

int main(int argc, char **argv) {
	ros::init(argc, argv, "parser"); // Initialize ROS node with name parser
	ros::NodeHandle n;
	sub = n.subscribe("driverparser1", 1000, UARTparser::receiveMsg);
	pub = n.advertise<communication::infoStruct>("parsercontroller1", 1000);

	UARTparser up1();
	
	ros::spin(); // Loop which calls callback if msgStruct is received on topic driverparser1

	return 0;
}

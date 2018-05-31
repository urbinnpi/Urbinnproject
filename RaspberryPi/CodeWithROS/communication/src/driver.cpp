#include "driver.h"
#include "uartdriver.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
	ros::init(argc, argv, "driver"); // Initialize ROS node with name parser
	ros::NodeHandle n;

	UARTdriver ud1;

	sub = n.subscribe("controllerdriver1", 1000, &UARTdriver::receiveMsg, &ud1);
	pub = n.advertise<communication::msgStruct>("driverparser1", 1000);
	ros::Rate loop_rate(10); // Set speed of while(ros::ok()) loop, 10 Hz at the moment
	
	while(ros::ok()) {
		ud1.readInput();

		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)
	}

	return 0;
}

#include "uartdriver.h"
#include "uartparser.h"
#include <iostream>

int UARTdriver::s;
communication::msgStruct msg;

UARTdriver::UARTdriver() {
	pub = nh.advertise<communication::msgStruct>("driverparser1", 1000);
	sub = nh.subscribe("controllerdriver1", 1000, &UARTdriver::receiveMsg, this);
	struct sockaddr_can addr;
	struct ifreq ifr;
	const char *ifname = "can0"; // CAN interface name
	
	// Open socket
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
	}
	
	// Copy the interface
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	// Add settings
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	
	// Bind socket
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
	}
}

void UARTdriver::readInput() {
	/*int recvbytes = read(s, msg, sizeof(communication::msgStruct));

	if(recvbytes) {
		communication::msgStruct msg2;
		msg2.id = msg.id;
		msg2.dl = msg.dl;
		msg2.data = msg.data;
		pub.publish(msg2);
	}*/
}

void UARTdriver::receiveMsg(communication::msgStruct& msg) { // Callback of topic controllerdriver1
	this->transmit(msg);
}

void UARTdriver::transmit(communication::msgStruct msg) {
	write(s, msg, sizeof(communication::msgStruct));
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "driver"); // Initialize ROS node with name parser
	UARTdriver ud1;
	ros::Rate loop_rate(10); // Set speed of while(ros::ok()) loop, 10 Hz at the moment
	
	while(ros::ok()) {
		ud1.readInput();

		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)
	}

	return 0;
}

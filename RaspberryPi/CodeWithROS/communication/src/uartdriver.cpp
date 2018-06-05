#include "uartdriver.h"
#include "uartparser.h"
#include <iostream>
#include "message.h"

int UARTdriver::s;
struct can_frame frame;

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
	int recvbytes = read(s, &frame, sizeof(struct can_frame));

	if(recvbytes) {
		communication::msgStruct msg;
		msg.id = frame.can_id;
		msg.dl = frame.can_dlc;
		for(uint8_t i = 0; msg.dl > i; i++) {
			msg.data[i] = frame.data[i];
		}
		ROS_INFO("Published message");
		pub.publish(msg);
	}
}

void UARTdriver::receiveMsg(const communication::msgStruct& msg) { // Callback of topic controllerdriver1
	this->transmit(msg);
}

void UARTdriver::transmit(const communication::msgStruct msg) {
	struct can_frame frame2;
	frame2.can_id = msg.id;
	frame2.can_dlc = msg.dl;
	for(uint8_t i = 0; frame2.can_dlc > i; i++) {
		frame2.data[i] = msg.data[i];
	}
	write(s, &frame2, sizeof(struct can_frame));
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "driver"); // Initialize ROS node with name parser
	UARTdriver ud1;
	ros::Rate loop_rate(10); // Set speed of while(ros::ok()) loop, 10 Hz at the moment
	
	while(ros::ok()) {
		ROS_INFO("Starting loop1");
		ms::message("Starting loop2");
		std::cout << "Staring loop3" << std::endl;
		
		ud1.readInput();

		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)
	}

	return 0;
}

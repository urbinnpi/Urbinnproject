#include "uartdriver.h"
#include "uartparser.h"
#include <iostream>
#include <thread>

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
		ROS_ERROR("Error while opening socket");
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
	ROS_INFO("Started UARTdriver");
}

void UARTdriver::readInput() {
	
	// keep looping
	while(1) {
		ROS_INFO("Getting CAN frame");
		
		// this function blocks while waiting
		int recvbytes = read(s, &frame, sizeof(struct can_frame));
	
		if(recvbytes) {
			ROS_INFO("Got can frame");

			communication::msgStruct msg;
			msg.id = frame.can_id;
			msg.dl = frame.can_dlc;
			for(uint8_t i = 0; msg.dl > i; i++) {
				msg.data[i] = frame.data[i];
				ROS_INFO("received data: %X", msg.data[i]);
			}
		
			pub.publish(msg);
		}
	}
}

void UARTdriver::receiveMsg(const communication::msgStruct& msg) { // Callback of topic controllerdriver1
	ROS_INFO("Received commando from controller");
	this->transmit(msg);
}

void UARTdriver::transmit(const communication::msgStruct msg) {
	ROS_INFO("Transmitting CAN frame with ID: 0x%X", msg.id);
	
	struct can_frame frame2;
	frame2.can_id = msg.id;
	frame2.can_dlc = msg.dl;
	for(uint8_t i = 0; frame2.can_dlc > i; i++) {
		frame2.data[i] = msg.data[i];
		ROS_INFO("Transmitting data: %X", frame2.data[i]);
 	}
	
 	write(s, &frame2, sizeof(struct can_frame));
	
	ROS_INFO("CAN frame send");
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "driver"); // Initialize ROS node with name parser
	UARTdriver ud1;
	ros::Rate loop_rate(10); // Set speed of while(ros::ok()) loop, 10 Hz at the moment

	ROS_INFO("Starting loop");

	std::thread t1(&UARTdriver::readInput, &ud1);
	ros::spin();
	/*while(ros::ok()) {
		ud1.readInput();

		ros::spinOnce(); // Execute callbacks if something is received on subscribed topics
		loop_rate.sleep(); // Make sure loop is running at given rate (10 Hz at the moment)	
	}*/
	t1.join();
	
	ROS_INFO("End of driver node");

	return 0;
}

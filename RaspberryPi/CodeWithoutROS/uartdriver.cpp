#include "uartdriver.h"
#include "uartparser.h"

UARTdriver::UARTdriver(): up1(new UARTparser()) {
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

UARTdriver::~UARTdriver() {
	delete up1;
}

void UARTdriver::readInput(struct can_frame *frame) {
	while(1) {
		int recvbytes = read(s, frame, sizeof(struct can_frame));

		// Bij gebruik ROS hier frame publishen op topic DriverParser1
		if(recvbytes) up1->receiveMsg(frame); // Tijdelijk gebruik van parser callback
	}
}

void UARTdriver::receiveMsg(struct can_frame *frame) { // Callback van topic ControllerDriver1
	this->transmit(frame);
}

void UARTdriver::transmit(struct can_frame *frame) {
	int nbytes;
	nbytes = write(s, frame, sizeof(struct can_frame)); // Write the frame
	/*
	int nbytes, id;
	while(1) {
		std::cin >> id;

		// Create the frame
		//frame->can_id  = 0x123;
		frame->can_id = id;
		frame->can_dlc = 2;
		frame->data[0] = 0x11;
		frame->data[1] = 0x22;

		nbytes = write(s, frame, sizeof(struct can_frame)); // Write the frame
	}
	*/
}

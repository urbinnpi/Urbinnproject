#include "uartdriver.h"
#include "uartparser.h"
#include <iostream>

int UARTdriver::s;
communication::msgStruct msg;

UARTdriver::UARTdriver() {
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
	int recvbytes = read(s, msg, sizeof(communication::msgStruct));

	if(recvbytes) {
		communication::msgStruct msg2;
		msg2.id = msg.id;
		msg2.dl = msg.dl;
		msg2.data = msg.data;
		pub.publish(msg2);
	}
}

void UARTdriver::receiveMsg(communication::msgStruct* msg) { // Callback of topic controllerdriver1
	this->transmit(msg);
}

void UARTdriver::transmit(communication::msgStruct* msg) {
	write(s, msg, sizeof(communication::msgStruct));
}

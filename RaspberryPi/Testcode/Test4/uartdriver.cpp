#include "uartdriver.h"
#include <iostream>
#include <thread>

int UARTdriver::s;
struct can_frame frame;

UARTdriver::UARTdriver() {
	struct sockaddr_can addr;
	struct ifreq ifr;
	const char *ifname = "can0"; // CAN interface name
	
	// Open socket
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		std::cout << "Error while opening socket" << std::endl;
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
	std::cout << "Started UARTdriver" << std::endl;
}

void UARTdriver::readInput() {
	while(1) {
		std::cout << "Getting CAN frame" << std::endl;
		int recvbytes = read(s, &frame, sizeof(struct can_frame));
	
		if(recvbytes) {
			std::cout << "Got can frame" << std::endl;

			communication::msgStruct msg;
			msg.id = frame.can_id;
			msg.dl = frame.can_dlc;
			std::cout << "ID: " << std::hex << msg.id << "  Received data:  ";
			
			for(uint8_t i = 0; msg.dl > i; i++) {
				msg.data[i] = frame.data[i];
				std::cout << std::hex << msg.data[i] << " "; 
			}
			std::cout << std::endl;
		}
	}
}

void UARTdriver::receiveMsg(const communication::msgStruct& msg) { // Callback of topic controllerdriver1
	std::cout << "Received commando from controller" << std::endl;
	this->transmit(msg);
}

void UARTdriver::transmit(const communication::msgStruct msg) {
	std::cout << "Transmitting CAN frame with ID: 0x" << std::hex <<msg.id << std::endl;
	
	struct can_frame frame2;
	frame2.can_id = msg.id;
	frame2.can_dlc = msg.dl;
	for(uint8_t i = 0; frame2.can_dlc > i; i++) {
		frame2.data[i] = msg.data[i];
		std::cout << "Transmitting data: " << frame2.data[i];
 	}
	std::cout << std::endl;
	
 	write(s, &frame2, sizeof(struct can_frame));
	
	std::cout << "CAN frame send" std::endl;
}

int main(int argc, char **argv) {
	UARTdriver ud1;
	
	std::cout << "Going to send a frame" << std::endl;

	struct can_frame frame;
	frame.can_id = 0x704
	frame.can_dlc = 4;
	frame.data[0] = 0xAA;
	frame.data[1] = 0xBB;
	frame.data[2] = 0xCC;
	frame.data[3] = 0xDD;
	
	write(s, &frame, sizeof(struct can_frame));
	
	std::cout << "Data send: " << std::endl;
	std::cout << "ID: " << std::hex << frame.id << "  Received data:  ";

	for(uint8_t i = 0; msg.dl > i; i++) {
		std::cout << std::hex << frame.data[i] << " "; 
	}
	
	std::cout << std::endl;

	return 0;
}

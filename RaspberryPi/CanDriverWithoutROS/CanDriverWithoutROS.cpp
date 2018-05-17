#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <stdint.h>
#include <iostream>
#include <chrono>
#include <thread>

#define SPAM_DELAY_MS 250

/******************************************************************************************************
*		Compile with: g++ CanDriverWithoutROS.cpp -o CanDriverWithoutROS -std=c++11 -pthread
*/

void send(struct can_frame *frame, int socket){
	int nbytes;
	
	// create frame
	frame->can_id  = 0x123;
	frame->can_dlc = 2; // data length
	frame->data[0] = 0x11;
	frame->data[1] = 0x22;
	
	// write the frame
	nbytes = write(socket, frame, sizeof(struct can_frame));
	
	// delay so we don't spam the CAN-bus
	std::this_thread::sleep_for(std::chrono::milliseconds(SPAM_DELAY_MS));
}

void receive(struct can_frame *frame, int socket){
	int recvbytes = read(socket, frame, sizeof(struct can_frame));
	if(recvbytes) {
		std::cout << "ID: " << std::uppercase << std::hex << (unsigned int)frame->can_id << " Length: " << (unsigned int)frame->can_dlc << " Data: ";
		
		// loop trough the data
		for(uint8_t i = 0; frame->can_dlc > i; i++) {
			//std::cout << " " << std::uppercase << std::hex << (unsigned int)frame->data[i];
			std::cout << " " << (char)frame->data[i];
		}
		
		// end of frame
		std::cout << std::endl;
	}
}

int main(void) {
	int s;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct can_frame frame2;
	struct ifreq ifr;
	
	
	// our CAN interface
	const char *ifname = "can0";
	
	// open socket
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}
	
	// copy the interface
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	// add settings
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	
	// bind socket
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}
	
	std::thread t1 (receive, &frame, s);
	//std::thread t2 (send, &frame2, s);
	
	while (true) {
		send(&frame2, s);
		//receive(&frame, s);
	}
	
	printf("Exit!");
	return 0;
}
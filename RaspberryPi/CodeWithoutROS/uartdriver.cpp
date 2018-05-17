#include "uartdriver.h"

UARTdriver::UARTdriver() {
	struct sockaddr_can addr;
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
}

void UARTdriver::readInput(struct can_frame *frame) {
	int recvbytes = read(s, frame, sizeof(struct can_frame));
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

void UARTdriver::readMsg() {

}

void UARTdriver::transmit(struct can_frame *frame){
    int nbytes;

    // create frame
    frame->can_id  = 0x123;
    frame->can_dlc = 2;
    frame->data[0] = 0x11;
    frame->data[1] = 0x22;

    // write the frame
    nbytes = write(s, frame, sizeof(struct can_frame));
} 

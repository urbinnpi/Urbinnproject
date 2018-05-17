#include "uartdriver.h"
#include "uartparser.cpp"

UARTdriver::UARTdriver(): p(new UARTparser) {
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

void UARTdriver::readInput(struct can_frame *frame) {
	int recvbytes = read(s, frame, sizeof(struct can_frame));

	/*if(recvbytes) {
		std::cout << "ID: " << std::uppercase << std::hex << (unsigned int)frame->can_id << " Length: " << (unsigned int)frame->can_dlc << " Data: ";
		
		// Loop trough the data
		for(uint8_t i = 0; frame->can_dlc > i; i++) {
			//std::cout << " " << std::uppercase << std::hex << (unsigned int)frame->data[i];
			std::cout << " " << (char)frame->data[i];
		}
		
		std::cout << std::endl; // End of frame
	}*/
	if(recvbytes) p->receiveMsg(frame); // Tijdelijk gebruik van parser callback
}

void UARTdriver::receiveMsg() {

}

void UARTdriver::transmit(struct can_frame *frame){
	int nbytes;

	// Create the frame
	frame->can_id  = 0x123;
	frame->can_dlc = 2;
	frame->data[0] = 0x11;
	frame->data[1] = 0x22;

	nbytes = write(s, frame, sizeof(struct can_frame)); // Write the frame
} 

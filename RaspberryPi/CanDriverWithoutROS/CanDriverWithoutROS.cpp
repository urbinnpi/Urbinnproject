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


void send(struct can_frame *frame, int socket){
	int nbytes;
	
	// create frame
	frame->can_id  = 0x123;
	frame->can_dlc = 2;
	frame->data[0] = 0x11;
	frame->data[1] = 0x22;
	
	// write the frame
	nbytes = write(socket, frame, sizeof(struct can_frame));
	
}

void receive(struct can_frame *frame, int socket){
	int recvbytes = read(socket, frame, sizeof(struct can_frame));
	if(recvbytes) {
		printf("dlc = %d, data = %s\n", frame->can_dlc, frame->data);
	}
}

int main(void) {
	int s;
	struct sockaddr_can addr;
	struct can_frame frame;
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

	while (true) {
		printf("sending frame");
		send(&frame, s);
		printf("receiving frame");
		receive();
		print("starting again");
	}
	
	printf("Exit1!");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <libgen.h>
#include <time.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "terminal.h"
#include "lib.h"

#define CAN_INTERFACE can0


int main(void) {
	printf("CanDriverWithoutROS\n");
	
	int flags, opt;
    int s;
    char *iface;
    struct sockaddr_can addr;
    struct ifreq ifr;
    
    struct can_msg
    {
        struct bcm_msg_head msg_head;
        struct can_frame frame[NFRAMES];
    } msg;
	
	/* Register signal handlers */
    if (signal(SIGINT, onsig)    == SIG_ERR ||
        signal(SIGTERM, onsig)   == SIG_ERR ||
        signal(SIGCHLD, SIG_IGN) == SIG_ERR)
    {
        perror(PROGNAME);
        return errno;
    }
	
	if ((s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM)) < 0) {
		printf("Error opening socket");
		return 1;
	}
	
	strncpy(ifr.ifr_name, iface, IFNAMSIZ);
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0)
    {
        perror(PROGNAME ": ioctl");
        return errno;
    }
	
	addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror(PROGNAME ": connect");
        return errno;
    }

    /* Set socket to non-blocking */
    flags = fcntl(s, F_GETFL, 0);
    if (flags < 0)
    {
        perror(PROGNAME ": fcntl: F_GETFL");
        return errno;
    }

    if (fcntl(s, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror(PROGNAME ": fcntl: F_SETFL");
        return errno;
    }

    /* Setup code */
    sigval = 0;

    msg.msg_head.opcode  = RX_SETUP;
    msg.msg_head.can_id  = 0x123;
    msg.msg_head.flags   = 0;
    msg.msg_head.nframes = 0;
    if (write(s, &msg, sizeof(msg)) < 0)
    {
        perror(PROGNAME ": write: RX_SETUP");
        return errno;
    }
	
	while (true) {
		ssize_t nbytes;
		
		nbytes = read(s, &msg, sizeof(msg));
		struct can_frame * const frame = msg.frame;
		unsigned char * const data = frame->data;
		const unsigned int dlc = frame->can_dlc;
		unsigned int i;

		/* Print the received CAN frame */
		printf("RX:  ");
		print_can_frame(frame);
		printf("\n");

		/* Modify the CAN frame to use our message ID */
		frame->can_id = MSGID;
		
		/* Increment the value of each byte in the CAN frame */
		for (i = 0; i < dlc; ++i) {
			data[i] += 1;
		}

		/* Set a TX message for sending this frame once */
		msg.msg_head.opcode  = TX_SEND;
		msg.msg_head.can_id  = 0;
		msg.msg_head.flags   = 0;
		msg.msg_head.nframes = 1;

		/* Write the message out to the bus */
		nbytes = write(s, &msg, sizeof(msg));
		if (nbytes < 0) {
			perror(PROGNAME ": write: TX_SEND");
		}
		else if (nbytes < (ssize_t)sizeof(msg))	{
			fputs(PROGNAME ": write: incomplete BCM message\n", stderr);
		}
		else {
			/* Print the transmitted CAN frame */
			printf("TX:  ");
			print_can_frame(frame);
			printf("\n");
		}
		
	}
	
	/* Close the CAN interface */
    if (close(s) < 0)
    {
        perror(PROGNAME ": close");
        return errno;
    }
	
	
	return 0;
}

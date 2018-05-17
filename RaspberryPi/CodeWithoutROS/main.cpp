/*
 * Compile with: g++ main.cpp -o ProgramV1 -std=c++11 -pthread
 */

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <iostream>
#include "socketcan/can.h"
//#include "controller.h"
//#include "parser.h"
//#include "uartdriver.h"
#include "controller.cpp"
#include "uartparser.cpp"
#include "uartdriver.cpp"

using namespace std;

int main(void) {
	struct can_frame frame;
	struct can_frame frame2;

	UARTdriver ud1;
	
	//std::thread t1 (receive, &frame, s);
	//std::thread t2 (send, &frame2, s);
	
	while (true) {
		ud1.transmit(&frame2);
		ud1.readInput(&frame);
	}
	
	return 0;
}

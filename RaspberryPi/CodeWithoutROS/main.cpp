#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "socketcan/can.h"

#include <stdint.h>
#include <iostream>
#include <thread>

//#include "controller.h"
//#include "parser.h"
//#include "uartdriver.h"
#include "uartdriver.cpp"

/******************************************************************************************************
*		Compile with g++ CanDriverWithoutROS.cpp -o CanDriverWithoutROS -std=c++11 -pthread
*/

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
	
	printf("Exit!");
	return 0;
}

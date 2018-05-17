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
#include <thread>
#include "socketcan/can.h"
//#include "controller.h"
//#include "parser.h"
//#include "uartdriver.h"
#include "controller.h"
#include "uartparser.h"
#include "uartdriver.h"

using namespace std;

void readInput(UARTdriver ud1) {
	while(1)
		ud1.readInput();
}

void transmit(UARTdriver ud1) {
	while(1)
		ud1.transmit();
}

int main(void) {
	//struct can_frame frame;
	//struct can_frame frame2;

	UARTdriver ud1;

	std::thread t1(readInput, ud1);
	std::thread t2(transmit, ud1);
	
	//std::thread t1(ud1.readInput);//, &frame);
	//std::thread t2(ud1.transmit);//, &frame2);
	
	/*while (true) {
		ud1.transmit(&frame2);
		ud1.readInput(&frame);
	}*/
	
	return 0;
}

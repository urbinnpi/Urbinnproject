/*
 * Compile with: g++ *.cpp -o ProgramV1 -std=c++11 -pthread
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
#include "uartdriver.h"

using namespace std;

int main(void) {
	struct can_frame frame;
	struct can_frame frame2;

	//UARTdriver ud1;
	UARTdriver* ud1 = new UARTdriver();

	//std::thread t1(ud1.readInput);//, &frame);
	//std::thread t2(ud1.transmit);//, &frame2);
	std::thread t1(&UARTdriver::readInput, ud1, &frame);
	//std::thread t2(&UARTdriver::transmit, ud1, &frame2);
	t1.join();
	//t2.join();

	//while(1) {
	//	ud1.transmit(&frame2);
	//	ud1.readInput(&frame);
	//}
	
	delete ud1;
	return 0;
}

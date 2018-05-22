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
#include "uartparser.h"
#include "sensorxparser.h"
#include "controller.h"

using namespace std;

int main(void) {
	struct can_frame frame;
	struct can_frame frame2;

	Controller* c1 = new Controller();
	SensorXparser* sxp1 = new SensorXparser(c1);
	UARTparser* up1 = new UARTparser(c1, sxp1);
	UARTdriver* ud1 = new UARTdriver(up1);

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
	
	delete c1;
	delete sxp1;
	delete up1;
	delete ud1;
	return 0;
}

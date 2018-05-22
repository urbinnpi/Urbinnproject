//#include <iostream>
#include "controller.h"
#include "uartdriver.h"

/*Controller::Controller() : ud1(new UARTdriver()) {
	
}

Controller::~Controller() {
	delete ud1;
}*/

void Controller::receiveInfo(struct can_frame *frame) {
	// Lees infostruct uit en voer aan de hand daarvan functies zoals steer of brake uit
	// Deze functies kunnen vervolgens messages sturen naar de driver met transmitMsg()
	frame->data[0] += 1;
	frame->data[1] += 1;
	//this->transmitMsg(frame);
	int nbytes;
	nbytes = write(UARTdriver::s, frame, sizeof(struct can_frame)); // Write the frame

	/*
	std::cout << "ID: " << std::uppercase << std::hex << (unsigned int)frame->can_id << " Length: " << (unsigned int)frame->can_dlc << " Data: ";

	// Loop trough the data
	for(uint8_t i = 0; frame->can_dlc > i; i++) {
		//std::cout << " " << std::uppercase << std::hex << (unsigned int)frame->data[i];
		std::cout << " " << (char)frame->data[i];
	}
	std::cout << std::endl; // End of frame
	*/
}

void Controller::transmitMsg(struct can_frame *frame) {
	// Bij gebruik ROS hier msgStruct publishen op topic ControllerDriver1
	//ud1->receiveMsg(frame); // Tijdelijk gebruik van driver callback
}
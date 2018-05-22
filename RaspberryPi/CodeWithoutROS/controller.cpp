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

	if(frame->can_id == 0x631) {
		std::string input;
		for(uint8_t i = 0; frame->can_dlc > i; i++) {
			input.append((char)frame->data[i]);
		}
		if(input == "aan") {
			//stuur aangezet
			frame->data = "aangezet";
		}
	}

	//frame->can_id += 1;
	//this->transmitMsg(frame);
	int nbytes;
	nbytes = write(UARTdriver::s, frame, sizeof(struct can_frame)); // Tijdelijk

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
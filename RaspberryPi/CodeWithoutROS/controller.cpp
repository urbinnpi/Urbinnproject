#include <iostream>
#include <string>
#include "controller.h"
#include "uartdriver.h"

/*Controller::Controller() : ud1(new UARTdriver()) {
	
}

Controller::~Controller() {
	delete ud1;
}*/

void Controller::receiveInfo(struct infoStruct *infoFrame)
{
	// Lees infostruct uit en voer aan de hand daarvan functies zoals steer of brake uit
	// Deze functies kunnen vervolgens messages sturen naar de driver met transmitMsg()

	if(infoFrame->id == 0x631) // Als data afkomstig is van bijv. ultrasoonsensor
	{
		// Voer bijv. functie steer() uit en geef frame mee of zet in buffer
		for(uint8_t i = 0; infoFrame->dl > i; i++) {
			//std::cout << (char)infoFrame->data[i];
		}
	}

	//frame->can_id += 1;
	//infoFrame->id += 1;
	//this->transmitMsg(frame);
	int nbytes;
	nbytes = write(UARTdriver::s, infoFrame, sizeof(struct infoStruct));//frame, sizeof(struct can_frame)); // Tijdelijk

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
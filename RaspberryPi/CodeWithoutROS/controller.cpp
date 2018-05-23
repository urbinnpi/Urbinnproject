//#include <iostream>
#include <string>
#include "controller.h"
#include "uartdriver.h"

void Controller::receiveInfo(struct can_frame *frame)
{
	// Lees infostruct uit en voer aan de hand daarvan functies zoals steer of brake uit
	// Deze functies kunnen vervolgens messages sturen naar de driver met transmitMsg()

	if(frame->can_id == 0x631)
	{
		// Voer bijv. functie steer() uit en geef frame mee of zet in buffer
		//infoFrame->data[0] += 1; // Test
		frame->can_id += 1;
	}

	// Stel msgFrame samen om bijv. motor aan te sturen
	/*struct can_frame frame;
	frame.can_id = infoFrame->id;
	frame.can_dlc = infoFrame->dl;
	for(uint8_t i = 0; infoFrame->dl > i; i++) {
		frame.data[i] = infoFrame->data[i];
	}*/

	//this->transmitMsg(frame);
	int nbytes;
	nbytes = write(UARTdriver::s, frame, sizeof(struct can_frame)); // Tijdelijke vervanging voor transmitMsg
}

void Controller::transmitMsg(struct can_frame *frame) {
	// Bij gebruik ROS hier msgStruct publishen op topic ControllerDriver1
	//ud1->receiveMsg(frame); // Tijdelijk gebruik van driver callback
}


/*
	std::cout << "ID: " << std::uppercase << std::hex << (unsigned int)frame->can_id << " Length: " << (unsigned int)frame->can_dlc << " Data: ";

	// Loop trough the data
	for(uint8_t i = 0; frame->can_dlc > i; i++) {
		//std::cout << " " << std::uppercase << std::hex << (unsigned int)frame->data[i];
		std::cout << " " << (char)frame->data[i];
	}
	std::cout << std::endl; // End of frame
	*/

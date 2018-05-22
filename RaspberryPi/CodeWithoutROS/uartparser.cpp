#include "uartparser.h"
#include "controller.h"
#include "sensorxparser.h"

UARTparser::UARTparser() : c(new Controller()) {
	IDmap.insert(std::pair<uint16_t,Parser*>(0x631, new SensorXparser));
}

UARTparser::~UARTparser() {
	delete c;
	std::map<uint16_t, Parser*>::iterator i;
	for(i = IDmap.begin(); i != IDmap.end(); i++)
		delete i->second;
}

void UARTparser::parseData(struct can_frame *frame)
{
	// Zoek in IDmap naar sensor die bij frame hoort en voer daar deze functie op uit
	IDmap.find((uint16_t)frame->can_id)->second->parseData(frame);

	// Info over de UART kan ook naar controller worden gestuurd door transmitInfo() van deze klasse uit te voeren

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

void UARTparser::receiveMsg(struct can_frame *frame) // Callback van topic DriverParser1
{
	this->parseData(frame);
}

void UARTparser::addPair(uint16_t n, Parser* p)
{
	IDmap.insert(std::pair<uint16_t,Parser*>(n, p));
}

void UARTparser::removePair(uint16_t n)
{
	IDmap.erase(n);
}

void UARTparser::transmitInfo(struct can_frame *frame)
{
	// Bij gebruik ROS hier infostruct publishen op topic ParserController1
	c->receiveInfo(frame); // Tijdelijk gebruik van controller callback
}

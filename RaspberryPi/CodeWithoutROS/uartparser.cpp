#include "uartparser.h"

void UARTparser::parseData(struct can_frame *frame)
{
	std::cout << "ID: " << std::uppercase << std::hex << (unsigned int)frame->can_id << " Length: " << (unsigned int)frame->can_dlc << " Data: ";

	// Loop trough the data
	for(uint8_t i = 0; frame->can_dlc > i; i++) {
		//std::cout << " " << std::uppercase << std::hex << (unsigned int)frame->data[i];
		std::cout << " " << (char)frame->data[i];
	}
	std::cout << std::endl; // End of frame
}

void UARTparser::receiveMsg(struct can_frame *frame)
{
	this->parseData(frame);
}

void UARTparser::addPair(uint8_t n, Parser* p)
{
	IDmap.insert(pair<uint8_t,Parser*>(n, p));
}

void UARTparser::removePair(uint8_t n)
{
	IDmap.erase(n);
}

void transmitInfo()
{
	// Zie .h-bestand
}
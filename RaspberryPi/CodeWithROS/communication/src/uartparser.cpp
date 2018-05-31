#include "uartparser.h"
#include "controller.h"
#include "sensorxparser.h"

UARTparser::UARTparser() {
	IDmap.insert(std::pair<uint16_t,Parser*>(0x631, new SensorXparser()));
}

UARTparser::~UARTparser() {
	std::map<uint16_t, Parser*>::iterator i;
	for(i = IDmap.begin(); i != IDmap.end(); i++)
		//delete i->second;
		IDmap.erase(i);
}

void UARTparser::parseData(communication::msgStruct* msg) {
	// Zoek in IDmap naar sensor die bij frame hoort en voer daar deze functie op uit
	std::map<uint16_t, Parser*>::iterator temp = IDmap.find((uint16_t)msg->can_id);
	
	if(temp != IDmap.end()) {
		(*temp)->second->parseData(msg);
	}

	// Info over de UART kan ook naar controller worden gestuurd door transmitInfo() van deze klasse uit te voeren
}

void UARTparser::receiveMsg(communication::msgStruct* msg) { // Callback van topic driverparser1
	parseData(msg);
}

void UARTparser::addPair(uint16_t n, Parser* p) {
	IDmap.insert(std::pair<uint16_t,Parser*>(n, p));
}

void UARTparser::removePair(uint16_t n) {
	IDmap.erase(n);
}

void UARTparser::transmitInfo(communication::infoStruct* info) {
	pub.publish(info);
}
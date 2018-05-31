#include "uartparser.h"
#include "controller.h"
#include "sensorxparser.h"

UARTparser::UARTparser() {
	pub = nh.advertise<communication::infoStruct>("parsercontroller1", 1000);
	sub = nh.subscribe("driverparser1", 1000, &UARTparser::receiveMsg, this);
	IDmap.insert(std::pair<uint32_t,Parser*>(0x631, new SensorXparser(&pub)));
}

UARTparser::~UARTparser() {
	std::map<uint16_t, Parser*>::iterator i;
	for(i = IDmap.begin(); i != IDmap.end(); i++)
		//delete i->second;
		IDmap.erase(i);
}

void UARTparser::parseData(const communication::msgStruct msg) {
	// Zoek in IDmap naar sensor die bij frame hoort en voer daar deze functie op uit
	/*std::map<uint32_t, Parser*>::iterator temp = IDmap.find(msg.id);
	
	if(temp != IDmap.end()) {
		(*temp)->second->parseData(msg);
	}*/

	// Info over de UART kan ook naar controller worden gestuurd door transmitInfo() van deze klasse uit te voeren
}

void UARTparser::receiveMsg(const communication::msgStruct& msg) { // Callback van topic driverparser1
	parseData(msg);
}

void UARTparser::addPair(uint32_t n, Parser* p) {
	IDmap.insert(std::pair<uint32_t,Parser*>(n, p));
}

void UARTparser::removePair(uint32_t n) {
	IDmap.erase(n);
}

void UARTparser::transmitInfo(communication::infoStruct info) {
	pub.publish(info);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "parser"); // Initialize ROS node with name parser
	UARTparser up1;
	
	ros::spin(); // Loop which calls callback if msgStruct is received on topic driverparser1

	return 0;
}

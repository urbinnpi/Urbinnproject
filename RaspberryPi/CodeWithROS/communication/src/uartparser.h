#ifndef UARTPARSER_H
#define UARTPARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <map>
#include "socketcan/can.h"
#include "parser.h"
#include "ros/ros.h"
#include "communication/msgStruct.h"
#include "communication/infoStruct.h"

class Controller;

class UARTparser : public Parser
{
public:
	UARTparser();
	~UARTparser();
	void parseData(const communication::msgStruct msg); // Called by receiveMsg()
	void receiveMsg(const communication::msgStruct& msg); // Callback of topic driverparser1
	void addPair(uint32_t, Parser*);
	void removePair(uint32_t);
private:
	void transmitInfo(communication::infoStruct info); // Publisher of topic parsercontroller1
	std::map<uint32_t, Parser*> IDmap;
	ros::NodeHandle nh;
	ros::Publisher pub;
	ros::Subscriber sub;
};

#endif // UARTPARSER_H
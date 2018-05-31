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
	UARTparser(ros::Publisher pub);
	~UARTparser();
	void parseData(communication::msgStruct* msg); // Wordt aangeroepen door receiveMsg()
	void receiveMsg(communication::msgStruct* msg); // Callback van topic DriverParser1
	void addPair(uint16_t, Parser*);
	void removePair(uint16_t);
private:
	void transmitInfo(communication::infoStruct* info); // Publisht op topic ParserController1
	std::map<uint16_t, Parser*> IDmap;
	ros::Publisher pub;
};

#endif // UARTPARSER_H
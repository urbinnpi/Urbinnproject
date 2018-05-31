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
#include <communication/msgstruct.h>
#include <communication/infostruct.h>

class Controller;

class UARTparser : public Parser
{
public:
	UARTparser();
	~UARTparser();
	void parseData(communication::msgStruct* msg); // Wordt aangeroepen door receiveMsg()
	void receiveMsg(communication::msgStruct* msg); // Callback van topic DriverParser1
	void addPair(uint16_t, Parser*);
	void removePair(uint16_t);
private:
	void transmitInfo(communication::infoStruct* info); // Publisht op topic ParserController1
	std::map<uint16_t, Parser*> IDmap;
};

#endif // UARTPARSER_H
#ifndef UARTPARSER_H
#define UARTPARSER_H

#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <iostream>
#include <map>
#include "socketcan/can.h"
#include "parser.h"

class Controller;

class UARTparser : public Parser
{
public:
	UARTparser();
	~UARTparser();
	void parseData(struct can_frame *frame); // Wordt aangeroepen door receiveMsg()
	void receiveMsg(struct can_frame *frame); // Callback van topic DriverParser1
	void addPair(uint16_t, Parser*);
	void removePair(uint16_t);
private:
	void transmitInfo(struct can_frame *frame); // Publisht op topic ParserController1
	std::map<uint16_t, Parser*> IDmap;
	Controller* c;
};

#endif // UARTPARSER_H
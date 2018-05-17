#ifndef UARTPARSER_H
#define UARTPARSER_H

#include <map>
#include <stdint.h> // Voor uint8_t
#include <iostream>
#include "parser.h"

class UARTparser : public Parser
{
public:
	UARTparser();
	void parseData(struct can_frame *frame); // Wordt aangeroepen door receiveMsg()
	void receiveMsg(struct can_frame *frame); // Callback of topic DriverParser1
	void addPair(uint8_t, Parser*);
	void removePair(uint8_t);
private:
	void transmitInfo(); // Publisht op topic ParserController1
	map<uint8_t, Parser*> IDmap;
};

#endif // UARTPARSER_H
#ifndef UARTPARSER_H
#define UARTPARSER_H

#include <map>
#include <stdint.h> // Voor uint8_t
#include "parser.h"

class UARTparser : public Parser
{
public:
	UARTparser();
	void parseData(/* messageStruct */); // Wordt aangeroepen door receiveMsg()
	void receiveMsg(); // Callback van topic DriverParser1
	void addPair(uint8_t, Parser*);
	void removePair(uint8_t);
private:
	void transmitInfo(); // Publisht op topic ParserController1
	map<uint8_t, Parser*> IDmap;
};

#endif // UARTPARSER_H
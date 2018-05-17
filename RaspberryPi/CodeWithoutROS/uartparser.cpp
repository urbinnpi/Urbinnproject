#include "uartparser.h"

void UARTparser::parseData()
{
	// Zie .h-bestand
}

void UARTparser::receiveMsg()
{
	// Zie .h-bestand
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
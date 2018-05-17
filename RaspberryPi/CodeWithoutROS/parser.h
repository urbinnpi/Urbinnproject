#ifndef PARSER_H
#define PARSER_H

class Parser
{
public:
	virtual ~Parser() {}
	virtual void parseData() = 0;
private:
	virtual void transmitInfo() = 0;
};

#endif // PARSER_H
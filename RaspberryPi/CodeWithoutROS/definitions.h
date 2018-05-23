#ifndef DEFINITIONS_H
#define DEFINITIONS_H

struct msgStruct {
	uint32_t id;
	uint8_t dl;
	uint8_t data[8];
};

struct infoStruct {
	uint32_t id;
	uint8_t dl;
	uint8_t data[8];
};

#endif // DEFINITIONS_H
#ifndef UARTDRIVER_H
#define UARTDRIVER_H
#include "driver.h"
#include <linux-can-utils>
class UARTdriver{
public:
    void readinput();
    void receiveMsg();
    void transmit(messageStruct);


private:




}


#endif // UARTDRIVER_H

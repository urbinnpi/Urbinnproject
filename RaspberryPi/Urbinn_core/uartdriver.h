#ifndef UARTDRIVER_H
#define UARTDRIVER_H
#include "driver.h"
#include <linux-can-utils>
class UARTdriver{
public:
         UARTdriver();
         ~UARTdriver(){}
    void readinput();
    void receiveMsg();
    void transmit(messageStruct);


private:




}


#endif // UARTDRIVER_H

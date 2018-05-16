#include "uartdriver.h"

UARTdriver::UARTdriver(){    }

void UARTdriver::readinputcan(struct can_frame *frame, int socket){
    int recvbytes = read(socket, frame, sizeof(struct can_frame));
    if(recvbytes) {
            std::cout << "ID: " << std::uppercase << std::hex << (unsigned int)frame->can_id << " Length: " << (unsigned int)frame->can_dlc << " Data: ";

            // loop trough the data
            for(uint8_t i = 0; frame->can_dlc > i; i++) {
                    std::cout << " " << std::uppercase <<std::hex << (unsigned int)frame->data[i];
            }

            // end of frame
            std::cout << std::endl;
    }
}

    }


 void receive(){
 }


void UARTdriver::transmitMsg(struct can_frame *frame, int socket){
    int nbytes;

    // create frame
    frame->can_id  = 0x123;
    frame->can_dlc = 2;
    frame->data[0] = 0x11;
    frame->data[1] = 0x22;

    // write the frame
    nbytes = write(socket, frame, sizeof(struct can_frame));


}

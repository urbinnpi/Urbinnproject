#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (Canbus.init(CANSPEED_500)) {
    Serial.println("CAN init done");
  } else {
    Serial.println("Error in CAN init");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

tCAN* receive(){
  tCAN message = null;
  
  if(cmp2515_check_message()) {
    if(mcp_get_message(&message)) {
      return &message;
    }
  }
  
}

void send(tCAN* message){
  tCAN message;

  message.id = 0x631; //formatted in HEX
  message.header.rtr = 0;
  message.header.length = 8; //formatted in DEC
  message.data[0] = 0xFF;
  message.data[1] = 0xFF;
  message.data[2] = 0xFF;
  message.data[3] = 0xFF;
  message.data[4] = 0xFF;
  message.data[5] = 0xFF;
  message.data[6] = 0xFF;
  message.data[7] = 0xFF;

  mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
  mcp2515_send_message(&message);
}


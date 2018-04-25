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
  tCAN message;
  if (mcp2515_check_message()) {
    if (mcp2515_get_message(&message)) {    
     Serial.print("ID: ");
     Serial.print(message.id,HEX);
     Serial.print(", ");
     Serial.print("Data: ");
     Serial.print(message.header.length,DEC);
     
     for(int i=0;i<message.header.length;i++) { 
        Serial.print(message.data[i],HEX);
        Serial.print(" ");
      }
     Serial.println("");
    }
  }
}

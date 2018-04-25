#include <Canbus.h>
char UserInput;
int data;
char buffer[456];  //Data will be temporarily stored to this buffer before being written to the file

//********************************Setup Loop*********************************//

void setup(){
Serial.begin(9600);
Serial.println("CAN-Bus Demo");

if(Canbus.init(CANSPEED_500))  /* Initialise MCP2515 CAN controller at the specified speed */
  {
    Serial.println("CAN Init ok");
  } else
  {
    Serial.println("Can't init CAN");
  } 
   
  delay(1000); 

Serial.println("Please choose a menu option.");
Serial.println("1.Speed");
Serial.println("2.RPM");
Serial.println("3.Throttle");
Serial.println("4.Coolant Temperature");
Serial.println("5.O2 Voltage");
Serial.println("6.MAF Sensor");

}



//********************************Main Loop*********************************//

void loop(){

  while(Serial.available()){
     UserInput = Serial.read();
  
    if (UserInput=='1'){
     Canbus.ecu_req(VEHICLE_SPEED, buffer);
     Serial.print("Vehicle Speed: ");
     Serial.println(buffer);
     delay(500);
    }
    else if (UserInput=='2'){
     Canbus.ecu_req(ENGINE_RPM, buffer);
     Serial.print("Engine RPM: ");
     Serial.println(buffer);
     delay(500);
    
    }
    else if (UserInput=='3'){
     Canbus.ecu_req(THROTTLE, buffer);
     Serial.print("Throttle: ");
     Serial.println(buffer);
     delay(500);
    
    }
    else if (UserInput=='4'){
     Canbus.ecu_req(ENGINE_COOLANT_TEMP, buffer);
     Serial.print("Engine Coolant Temp: ");
     Serial.println(buffer);
     delay(500);
    
    }
    else if (UserInput=='5'){
     Canbus.ecu_req(O2_VOLTAGE, buffer);
     Serial.print("O2 Voltage: ");
     Serial.println(buffer);
     delay(500);
    
    }
    else if (UserInput=='6'){
     Canbus.ecu_req(MAF_SENSOR, buffer);
     Serial.print("MAF Sensor: ");
     Serial.println(buffer);
     delay(500);
    
    }
    else
    {
      Serial.println(UserInput);
      Serial.println("Not a valid input.");
      Serial.println("Please enter a valid option.");
    }
  
  }
}

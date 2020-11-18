#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"

EMGclass xbee;
Dynamixelclass Dynamix;

  
void xBeeRead(){
  xbee.updateData();
}
 
void setup() {
  Serial.begin(57600);
  xbee.begin(Serial1, 115200);
  Dynamix.begin(Serial2, 57600, 3);
  //Serial2.begin(57600);
  //Dynamix.begin1(Serial, 57600);
  //Dynamix.ping(01);
 Dynamix.setEnableTorque(254, 1,03);
  }

  
//IntervalTimer timer(10, xBeeRead);

void loop() {
    //while(!Serial1){}
    //while(!Serial){}

  //timer.update();
  //Serial.println(xbee.getEMG_CH1());
  //delay(25);
  
  //delay(1000);
  //Dynamix.setPosition(01, 3000);
//  Dynamix.ping(01);

  //delay(1000);

Serial.println("sent\n");
  delay(1000);

  Dynamix.setPMW(4,400,04);
  Dynamix.setPMW(5,-400,04);
  Dynamix.setAction(0xFE);

  delay(1000);
//Dynamix.setEnableTorque(1,0,03);

  //Dynamix.setPosition(01, 2000);
  //delay(200);
  //Dynamix.ping(01);
  //unsigned char *p;
  //p = Dynamix.readPacket();
 // for(int j=0; j<20; j++){
  //    Serial.print(" ");
  //    Serial.print(p[j], HEX);
  //  }
 //   Serial.println("");
}

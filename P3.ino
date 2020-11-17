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
  Serial2.begin(57600);
  //Dynamix.begin1(Serial, 57600);
  //Dynamix.ping(01);
  Dynamix.enableTorque(254, 01);
  }

  
IntervalTimer timer(10, xBeeRead);

void loop() {
    while(!Serial1){}
    while(!Serial){}

  //timer.update();
  //Serial.println(xbee.getEMG_CH1());
  //delay(25);
  
  delay(2000);
  Dynamix.setPosition(01, 3000);
  delay(2000);
  Dynamix.setPosition(01, 2000);
  delay(200);
  Dynamix.ping(01);
  unsigned char *p;
  p = Dynamix.readPacket();
  for(int j=0; j<20; j++){
      Serial.print(" ");
      Serial.print(p[j], HEX);
    }
    Serial.println("");
}

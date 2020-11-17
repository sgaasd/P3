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
  Dynamix.ping(01);
  }

  
IntervalTimer timer(10, xBeeRead);

void loop() {
    while(!Serial1){}
    while(!Serial){}

  timer.update();
  Serial.println(xbee.getEMG_CH1());
  delay(25);
}

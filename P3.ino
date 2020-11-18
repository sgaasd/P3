#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"
#include "src/libs/Elegoo_TFTLCD/Elegoo_TFTLCD.h"

EMGclass xbee;
Dynamixelclass Dynamix;

  bool start = false;
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
  }

  void startup(){
  Dynamix.setEnableTorque(254, 0, 03);
  delay(100);
  Dynamix.setOperationMode(254, 16, 3);
  delay(100);
  //Dynamix.setOperationMode(2, 16, 3);
  delay(100);
  //Dynamix.setOperationMode(5, 16, 3);
  delay(100);
  Dynamix.setEnableTorque(254, 01, 03);
  }
//IntervalTimer timer(10, xBeeRead);

void loop() {
    while(!Serial1){}
    while(!Serial){}
    if(start == false){
      startup();
      start = true;
    }
unsigned short val = 30000;
  //timer.update();
  //Serial.println(xbee.getEMG_CH1());
  //delay(25);
  
  delay(500);
  //Dynamix.setPosition(01, 3000);
//  Dynamix.ping(01);
  Serial.println(Dynamix.ping(01), HEX);
  delay(500);
  Dynamix.setPWM(2, val, 3);
  delay(100);
  Serial.print("PWM");
  Serial.println(Dynamix.getPWM(2));
  //Dynamix.setPosition(01, 2000);
  delay(2000);
  //Dynamix.ping(01);
  //unsigned char *p;
  //p = Dynamix.readPacket();
 // for(int j=0; j<20; j++){
  //    Serial.print(" ");
  //    Serial.print(p[j], HEX);
  //  }
 //   Serial.println("");
}

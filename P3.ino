#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"
#include "src/libs/Elegoo_TFTLCD/Elegoo_TFTLCD.h"

EMGclass xbee;
Dynamixelclass Dynamix;


bool start = false;
void xBeeRead() {
  xbee.updateData();
}
bool ref = true;
float value = 0;
float Lastvalue = 0;
float realValue;



void setup() {
  pinMode(31, INPUT);
  Serial.begin(57600);
  xbee.begin(Serial1, 115200);
  Dynamix.begin(Serial2, 57600, 3);
  delay(1000);
  Dynamix.setStatusReturnLevel(02, 01, 03);
  Dynamix.setMaxPosition(02, 3600, 03);
  Dynamix.setMinPosition(02, 1000, 03);
  
 Dynamix.setEnableTorque(02, 01, 03);
  Dynamix.setGain(02, 200, 03, 'p');
  Dynamix.setGain(02, 20, 03, 'i');
  Dynamix.setGain(02, 20, 03, 'd');
  Dynamix.setAccelerationProfile(02, 100, 03);
  Dynamix.setVelocityProfile(02, 50, 03);


}


void startup() {
  for (int i = 0; i < 10; i++) {
    Dynamix.getPosition(02);
    delay(10);
  }
}
bool moving= false;
void loop() {
  while (!Serial2) {}
  startup();
  value = Dynamix.getPosition(02);
 //Serial.println(value);

    realValue = value + 100;


    delay(2);
    Dynamix.setPosition(02, 3000, 03); 
    delay(1);
    Serial.println("reg_write1");
    delay(1000);
    Dynamix.setAction(02);
    delay(1);
    moving = Dynamix.getMoving(02);
    while(moving==true){
      moving = Dynamix.getMoving(02);
      delay(2);
      Serial.println("moving1");}
      
    delay(2);
    Dynamix.setPosition(02, 1000, 03); 
    delay(1);
    Serial.println("reg_write2");
    delay(1000);
    Dynamix.setAction(02);
    delay(1);
   while(moving==true){
      moving = Dynamix.getMoving(02);
      delay(2);
      Serial.println("moving2");}
}

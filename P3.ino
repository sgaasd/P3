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
short value = 0;
short Lastvalue = 0;
short realValue;

void getPOS() {
  value = Dynamix.getPosition(02);
  delay(2);
  while(digitalRead(31) == true){
    Serial.println("aktiv");
    Serial.println(value);
    Dynamix.setPosition(02, value + 200, 03);
    delay(1000);
Dynamix.getPosition(02);
  }
}


void setup() {
  pinMode(31, INPUT);
  Serial.begin(57600);
  xbee.begin(Serial1, 115200);
  Dynamix.begin(Serial2, 57600, 3);
  delay(1000);
  Dynamix.setEnableTorque(02, 01, 03);
  Dynamix.setAccelerationProfile(02, 600, 03);
  Dynamix.setVelocityProfile(02, 100, 03);
}

IntervalTimer timer(1, getPOS);

void startup() {
  for (int i = 0; i < 10; i++) {
    Dynamix.getPosition(02);
    delay(10);
  }
}

void loop() {
  while (!Serial2) {}
  startup();
  timer.update();
  delay(10);
  
  
  
  
}



//
//  Serial.println(value);
//  delay(2);
//  if(ref == true){
//    for(int i=0; i<100; i++){
//      realValue = value + i + 10;
//      Dynamix.setPosition(02, realValue, 03);
//      delay(1);
//      ref = false;
//      }
//    }
//  else if(ref == false){
//  realValue = value - 1000;
//  Dynamix.setPosition(02, realValue, 03);
//  delay(1);
//  ref = true;}

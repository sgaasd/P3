#include "CrustCrawler.h"

#define CONTROL_PIN 5


uint8_t ID[5] = {1, 2, 3, 4, 5};

CrustCrawler robot;

void setup() {
  Serial.begin(115200);
  robot.begin(Serial1, CONTROL_PIN, ID);
  delay(10);
  robot.profileVelocity(23);
  delay(10);
  robot.enableTorque(true);
  delay(3000);
}

void loop() {
  robot.goalVelocity(1, 20);
  delay(1000);
  robot.goalVelocity(1, -20);
  delay(1000);
}

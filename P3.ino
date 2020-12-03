#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"
#include "src/libs/Elegoo_TFTLCD/Elegoo_TFTLCD.h"

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
//Det er fordi jeg elskser alle farver...
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define JOINT_1 0x01
#define JOINT_2 0x02
#define JOINT_3 0x03
#define GRIPPER_LEFT 0x04
#define GRIPPER_RIGHT 0x05
#define GRIPPER_BOTH 0x0A // Shadow ID 10

#define WRITE 0x03
#define REQ_WRITE 0x04

#define DIRECTION_PIN 13


EMGclass xbee;
Dynamixelclass Dynamix;
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// controlling buttons
int upButton = 52;
int downButton = 53;
int selectButton = 51;
int menu = 0; //menu value for switch
int y = 0;    // variable y koordinate for pointer (arrow)
bool MainMenu = true; // to check which menu the user is in
// Point states which are used to tell whether or not the custom points store coordinates in them (green or red)
bool Point1State = false;
bool Point2State = false;
bool Point3State = false;
bool Point4State = false;
int sensorMin = 1023; // almost random number for calibration
int sensorMax = 0; // same as above
int sensorValue = 0; // accelerometer input
int PointerY[5] = {35, 70, 105, 140, 170}; // array with y coordinates for pointer
int gripperPos = 0; // 0=open, 1=closed


void setup() {
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  xbee.begin(Serial1, 115200);
  Dynamix.begin(Serial2, 57600, DIRECTION_PIN);
  delay(1000);
  while (!Serial2) {}
  Dynamix.setStatusReturnLevel(JOINT_1, 01, WRITE);
  Dynamix.setStatusReturnLevel(JOINT_2, 01, WRITE);
  Dynamix.setStatusReturnLevel(JOINT_3, 01, WRITE);
  Dynamix.setStatusReturnLevel(GRIPPER_LEFT, 01, WRITE);
  Dynamix.setStatusReturnLevel(GRIPPER_RIGHT, 01, WRITE);


  Dynamix.setOperationMode(JOINT_1, 03, WRITE);
  Dynamix.setOperationMode(JOINT_2, 03, WRITE);
  Dynamix.setOperationMode(JOINT_3, 03, WRITE);
  Dynamix.setOperationMode(GRIPPER_LEFT, 03, WRITE);
  Dynamix.setOperationMode(GRIPPER_RIGHT, 03, WRITE);


  Dynamix.setMaxPosition(JOINT_1, 4095, WRITE);
  Dynamix.setMinPosition(JOINT_1, 0, WRITE);

  Dynamix.setMaxPosition(JOINT_2, 3280, WRITE);
  Dynamix.setMinPosition(JOINT_2, 754, WRITE);

  Dynamix.setMaxPosition(JOINT_3, 3280, WRITE);
  Dynamix.setMinPosition(JOINT_3, 742, WRITE);

  Dynamix.setMaxPosition(GRIPPER_LEFT, 3200, WRITE);
  Dynamix.setMinPosition(GRIPPER_LEFT, 2000, WRITE);

  Dynamix.setMaxPosition(GRIPPER_RIGHT, 3200, WRITE);
  Dynamix.setMinPosition(GRIPPER_RIGHT, 2000, WRITE);


  Dynamix.setEnableTorque(JOINT_1, 01, WRITE);
  Dynamix.setEnableTorque(JOINT_2, 01, WRITE);
  Dynamix.setEnableTorque(JOINT_3, 01, WRITE);
  Dynamix.setEnableTorque(GRIPPER_LEFT, 01, WRITE);
  Dynamix.setEnableTorque(GRIPPER_RIGHT, 01, WRITE);


  Dynamix.setGain(JOINT_1, 600, WRITE, 'p');
  Dynamix.setGain(JOINT_1, 20, WRITE, 'i');
  Dynamix.setGain(JOINT_1, 20, WRITE, 'd');

  Dynamix.setGain(JOINT_2, 600, WRITE, 'p');
  Dynamix.setGain(JOINT_2, 20, WRITE, 'i');
  Dynamix.setGain(JOINT_2, 20, WRITE, 'd');

  Dynamix.setGain(JOINT_3, 600, WRITE, 'p');
  Dynamix.setGain(JOINT_3, 20, WRITE, 'i');
  Dynamix.setGain(JOINT_3, 20, WRITE, 'd');

  Dynamix.setGain(GRIPPER_LEFT, 600, WRITE, 'p');
  Dynamix.setGain(GRIPPER_LEFT, 20, WRITE, 'i');
  Dynamix.setGain(GRIPPER_LEFT, 20, WRITE, 'd');

  Dynamix.setGain(GRIPPER_RIGHT, 600, WRITE, 'p');
  Dynamix.setGain(GRIPPER_RIGHT, 20, WRITE, 'i');
  Dynamix.setGain(GRIPPER_RIGHT, 20, WRITE, 'd');


  Dynamix.setAccelerationProfile(JOINT_1, 100, WRITE);
  Dynamix.setVelocityProfile(JOINT_1, 200, WRITE);

  Dynamix.setAccelerationProfile(JOINT_2, 50, WRITE);
  Dynamix.setVelocityProfile(JOINT_2, 100, WRITE);

  Dynamix.setAccelerationProfile(JOINT_3, 20, WRITE);
  Dynamix.setVelocityProfile(JOINT_3, 100, WRITE);

  Dynamix.setAccelerationProfile(GRIPPER_LEFT, 20, WRITE);
  Dynamix.setVelocityProfile(GRIPPER_LEFT, 100, WRITE);

  Dynamix.setAccelerationProfile(GRIPPER_RIGHT, 20, WRITE);
  Dynamix.setVelocityProfile(GRIPPER_RIGHT, 100, WRITE);

  Dynamix.setPosition(JOINT_1, 2047, REQ_WRITE);
  delay(2);
  Dynamix.setPosition(JOINT_2, 3073, REQ_WRITE);
  delay(2);
  Dynamix.setPosition(JOINT_3, 2047, REQ_WRITE);
  delay(2);
  Dynamix.setPosition(GRIPPER_BOTH, 2047, REQ_WRITE);
  delay(2);
  gripperPos = 1;
  // Dynamix.setPosition(05, 2047, 04);
  delay(2);
  Dynamix.setAction(0xFE);
  delay(2000);

  tft.reset(); // reset the display
  tft.begin(0x9341); // start communication with the display on given address
  pinMode(upButton, INPUT_PULLUP); // buttons for menu control
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  tft.fillScreen(BLACK); //fill whole screen with color black (not required, but then the screen will flash with grey colors)
  callibration(); // calibration function
  tft.fillScreen(BLACK);
  updateMenu(); // updating the switch menu state

}
//Print main menu
void PrintMainMenu() {
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.setCursor(70, 35);
  tft.print(" Joint 1 ");
  tft.setCursor(70, 70);
  tft.print(" Joint 2 ");
  tft.setCursor(70, 105);
  tft.print(" Joint 3 ");
  tft.setCursor(70, 140);
  tft.print(" Gripper " );
  tft.setCursor(70, 175);
  tft.print(" Points ");
}
//Print sub menu
void PrintSubMenu() {
  if (Point1State == true) {
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70, 35);
    tft.print(" Point 1 ");
  }
  else {
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70, 35);
    tft.print(" Point 1 ");
  }
  if (Point2State == true) {
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70, 70);
    tft.print(" Point 2 ");
  }
  else {
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70, 70);
    tft.print(" Point 2 ");
  }
  if (Point3State == true) {
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70, 105);
    tft.print(" Point 3 ");
  }
  else {
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70, 105);
    tft.print(" Point 3 ");
  }
  if (Point4State == true) {
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70, 140);
    tft.print(" Point 4 ");
  }
  else {
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70, 140);
    tft.print(" Point 4 ");
  }
  tft.setTextColor(WHITE); tft.setTextSize(3);
  tft.setCursor(70, 175);
  tft.print(" Back<- ");
}

//Print Pointer
void printPointer() {
  tft.setTextColor(WHITE); tft.setTextSize(3);
  tft.setCursor(40, PointerY[y]);
  tft.print("->");
}

void startup() {
  for (int i = 0; i < 10; i++) {
    Dynamix.getPosition(JOINT_1);
    delay(6);
    Dynamix.getPosition(JOINT_2);
    delay(6);
    Dynamix.getPosition(JOINT_3);
    delay(6);
    Dynamix.getPosition(GRIPPER_LEFT);
    delay(6);
    Dynamix.getPosition(GRIPPER_RIGHT);
    delay(6);
  }

}

// the menu, where only pointer moves
void updateMenu() {
  if (MainMenu == true) { // prints the main menu IF the user IS in the main menu
    PrintMainMenu();
  };
  switch (menu) {
    case 0:
      tft.fillRect(40, 0, 33, 240, BLACK);
      printPointer();
      break;
    case 1:
      tft.fillRect(40, 0, 33, 240, BLACK);
      printPointer();
      break;
    case 2:
      tft.fillRect(40, 0, 33, 240, BLACK);
      printPointer();
      break;
    case 3:
      tft.fillRect(40, 0, 33, 240, BLACK);
      printPointer();
      break;
    case 4:
      tft.fillRect(40, 0, 33, 240, BLACK);
      printPointer();

      break;
  }
}

void execute() {  //the "select" function
  switch (menu) {
    case 0:
      if (MainMenu == false) { //cheks if the user is in the main menu

        if (Point1State == false) { // checks wheter or not the points "store" coordinates in them
          tft.setTextColor(RED);  tft.setTextSize(3); //sets the color, text size and the coordinates for the text location
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 1 "); //prints text to the screen, where "0" is ordinary print and "1" is println
          Point1State = true;
        }
        else if (Point1State == true) {
          tft.setTextColor(GREEN);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 1 ");
          Point1State = false;
        }
      }
      break;
    case 1:
      if (MainMenu == false) {

        if (Point2State == false) {
          tft.setTextColor(RED);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 2 ");
          Point2State = true;
        }
        else if (Point2State == true) {
          tft.setTextColor(GREEN);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 2 ");
          Point2State = false;
        }
      }
      break;

    case 2:
      if (MainMenu == false) {

        if (Point3State == false) {
          tft.setTextColor(RED);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 3 ");
          Point3State = true;
        }
        else if (Point3State == true) {
          tft.setTextColor(GREEN);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 3 ");
          Point3State = false;
        }
      }
      break;

    case 3:
      if (MainMenu == false) {

        if (Point4State == false) {
          tft.setTextColor(RED);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 4 ");
          Point4State = true;
        }
        else if (Point4State == true) {
          tft.setTextColor(GREEN);  tft.setTextSize(3);
          tft.setCursor(70, PointerY[y]);
          tft.print(" Point 4 ");
          Point4State = false;
        }
      }
      break;
    case 4:
      tft.fillScreen(BLACK);
      if (MainMenu == true) {
        PrintSubMenu();
        MainMenu = false;
      }
      else {
        tft.fillScreen(BLACK);
        PrintMainMenu();
        MainMenu = true;
      }
      break;
  }
}
void callibration() { //not actually used yet
  while (millis() < 5000)
  {
    tft.setTextColor(GREEN);  tft.setTextSize(2);
    tft.setCursor(70, PointerY[y]);
    tft.print(" Shake ur head along X-axis");
    xbee.updateData();
    sensorValue = xbee.getAccX(); //sets the sensorValue to the input from the accelerometer
    Serial.println(sensorValue); // just to display the resulting number
    if (sensorValue > sensorMax) { // record the maximum sensor value
      sensorMax = sensorValue;
    }
    if (sensorValue < sensorMin) {// record the minimum sensor value
      sensorMin = sensorValue;
    }

    sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
    tft.setTextColor(GREEN);  tft.setTextSize(2);
    tft.setCursor(70, PointerY[y]);
    tft.print(sensorValue);
  }
}

void PrimeMover(int a){
  
}

void moving() {
  if (menu == 0)
  {
    int32_t joint1 = Dynamix.getPosition(JOINT_1);
    int32_t sendjointN1 = joint1 - 40;
    int32_t sendjointP1 = joint1 + 40;
    delay(6);
    if (digitalRead(10)) {
      Dynamix.setPosition(JOINT_1, sendjointN1, WRITE);
        while((sendjointN1-10)>Dynamix.getPosition(JOINT_1)>(sendjointN1+10)){
        delay(6);
        Serial.println("waiting...");
        }

      Serial.println("OUT");
    }
    else if (digitalRead(11)) {
      Dynamix.setPosition(JOINT_1, sendjointP1, WRITE);
      while(Dynamix.getMoving(JOINT_1)==0){
             delay(6);
        Serial.println("waitin2g...");
        }
        
              Serial.println("OUT2");

    }

    while (!digitalRead(10)&&digitalRead(10))
    {
      /* code */
    }


    
  }
  else if (menu == 1)
  {
    int32_t joint2 = Dynamix.getPosition(JOINT_2);
    int32_t sendjointN2 = joint2 - 40;
    int32_t sendjointP2 = joint2 + 40;
    delay(6);
    if (digitalRead(10)) {
      Dynamix.setPosition(JOINT_2, sendjointN2, WRITE);
      delay(90);
    }
    else if (digitalRead(11)) {
      Dynamix.setPosition(JOINT_2, sendjointP2, WRITE);
      delay(90);
    }
  }
  else if (menu == 2)
  {
    int32_t joint3 = Dynamix.getPosition(JOINT_3);
    int32_t sendjointN3 = joint3 - 40;
    int32_t sendjointP3 = joint3 + 40;
    delay(6);
    if (digitalRead(10)) {
      Dynamix.setPosition(JOINT_3, sendjointN3, WRITE);
      delay(90);
    }
    else if (digitalRead(11)) {
      Dynamix.setPosition(JOINT_3, sendjointP3, WRITE);
      delay(90);
    }
  }
  else if (menu == 3)
  {
    int32_t gripper = Dynamix.getPosition(GRIPPER_LEFT);
    int32_t gripperN = gripper - 30;
    int32_t gripperP = gripper + 30;
    delay(6);
    if (digitalRead(10)) {
      Dynamix.setPosition(GRIPPER_BOTH, gripperP, WRITE); // gripper opens
      delay(6);
      Serial.println(gripper);
    }
    else if (digitalRead(11)) {
      Dynamix.setPosition(GRIPPER_BOTH, gripperN, WRITE); // gripper closes
      delay(6);
    }
    
  }
  
}
void loop() {
  while (!Serial2) {}
  startup();
  float hertz = 1000 / 200;
  long old_time;

  while (true) {


    old_time = millis();

    xbee.updateData();

    if (!digitalRead(upButton)) { // resting is around 560
      menu++;
      y++;
      if (menu > 4) {
        menu = 0;
        y = 0;
      }
      updateMenu();

      //delay(50);
      //while (!digitalRead(downButton));
    }
    if (!digitalRead(downButton)) { // resting is around 560
      menu--;
      y--;
      if (menu < 0) {
        menu = 4;
        y = 4;
      }
      updateMenu();

      delay(2);
      //while (!digitalRead(upButton));
    }
    if (!digitalRead(selectButton)) { // resting is around 0
      execute();
      ///updateMenu();
      delay(2);
      while (!digitalRead(selectButton));
    }
    moving();
//    if(Dynamix.getMoving(01)==0){
//    while(Serial2.available()){
//                             Serial2.read();
//}}
    while (millis() - old_time < hertz);
  }
}

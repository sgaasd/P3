#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"
#include "src/libs/Elegoo_TFTLCD/Elegoo_TFTLCD.h"
//#include "src/libs/Elegoo_GFX/Elegoo_GFX.h"

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


EMGclass xbee;
Dynamixelclass Dynamix;
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

bool start = false;
void xBeeRead() {
  xbee.updateData();
}
bool ref = true;
float value = 0;
float Lastvalue = 0;
float realValue;

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


void setup() {
  pinMode(31, INPUT);
  Serial.begin(9600);
  xbee.begin(Serial1, 115200);
  Dynamix.begin(Serial2, 57600, 3);
  delay(1000);
  while (!Serial2) {}
  Dynamix.setStatusReturnLevel(01, 01, 03);
  Dynamix.setStatusReturnLevel(02, 01, 03);
  Dynamix.setStatusReturnLevel(03, 01, 03);
  Dynamix.setStatusReturnLevel(04, 01, 03);
  Dynamix.setStatusReturnLevel(05, 01, 03);


  Dynamix.setOperationMode(01, 03, 03);
  Dynamix.setOperationMode(02, 03, 03);
  Dynamix.setOperationMode(03, 03, 03);
  Dynamix.setOperationMode(04, 03, 03);
  Dynamix.setOperationMode(05, 03, 03);


  Dynamix.setMaxPosition(01, 4095, 03);
  Dynamix.setMinPosition(01, 0, 03);

  Dynamix.setMaxPosition(02, 3280, 03);
  Dynamix.setMinPosition(02, 754, 03);

  Dynamix.setMaxPosition(03, 3280, 03);
  Dynamix.setMinPosition(03, 742, 03);

  Dynamix.setMaxPosition(04, 3200, 03);
  Dynamix.setMinPosition(04, 2000, 03);

  Dynamix.setMaxPosition(05, 3200, 03);
  Dynamix.setMinPosition(05, 2000, 03);


  Dynamix.setEnableTorque(01, 01, 03);
  Dynamix.setEnableTorque(02, 01, 03);
  Dynamix.setEnableTorque(03, 01, 03);
  Dynamix.setEnableTorque(04, 01, 03);
  Dynamix.setEnableTorque(05, 01, 03);


  Dynamix.setGain(01, 600, 03, 'p');
  Dynamix.setGain(01, 20, 03, 'i');
  Dynamix.setGain(01, 20, 03, 'd');

  Dynamix.setGain(02, 600, 03, 'p');
  Dynamix.setGain(02, 20, 03, 'i');
  Dynamix.setGain(02, 20, 03, 'd');

  Dynamix.setGain(03, 600, 03, 'p');
  Dynamix.setGain(03, 20, 03, 'i');
  Dynamix.setGain(03, 20, 03, 'd');

  Dynamix.setGain(04, 600, 03, 'p');
  Dynamix.setGain(04, 20, 03, 'i');
  Dynamix.setGain(04, 20, 03, 'd');

  Dynamix.setGain(05, 600, 03, 'p');
  Dynamix.setGain(05, 20, 03, 'i');
  Dynamix.setGain(05, 20, 03, 'd');


  Dynamix.setAccelerationProfile(01, 20, 03);
  Dynamix.setVelocityProfile(01, 100, 03);

  Dynamix.setAccelerationProfile(02, 20, 03);
  Dynamix.setVelocityProfile(02, 100, 03);

  Dynamix.setAccelerationProfile(03, 20, 03);
  Dynamix.setVelocityProfile(03, 100, 03);

  Dynamix.setAccelerationProfile(04, 20, 03);
  Dynamix.setVelocityProfile(04, 100, 03);

  Dynamix.setAccelerationProfile(05, 20, 03);
  Dynamix.setVelocityProfile(05, 100, 03);

  Dynamix.setPosition(01, 2047, 04);
  delay(2);
  Dynamix.setPosition(02, 3073, 04);
  delay(2);
  Dynamix.setPosition(03, 2047, 04);
  delay(2);
  Dynamix.setPosition(10, 2047, 04);
  delay(2);
  // Dynamix.setPosition(05, 2047, 04);
  delay(2);
  Dynamix.setAction(0xFE);
  delay(2000);
<<<<<<< HEAD

=======
  
>>>>>>> 078cf16695f26547c889b803e2755c1c3ffc740f
    tft.reset(); // reset the display
    tft.begin(0x9341); // start communication with the display on given address
    pinMode(upButton, INPUT_PULLUP); // buttons for menu control
    pinMode(downButton, INPUT_PULLUP);
    pinMode(selectButton, INPUT_PULLUP);
    tft.fillScreen(BLACK); //fill whole screen with color black (not required, but then the screen will flash with grey colors)
    callibration(); // calibration function
    tft.fillScreen(BLACK);
    updateMenu(); // updating the switch menu state
<<<<<<< HEAD

=======
  
>>>>>>> 078cf16695f26547c889b803e2755c1c3ffc740f
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
    Dynamix.getPosition(02);
    delay(10);
  }
}
bool moving = false;

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

void moving(){
  switch (menu)
    {
      case 0:
        /* Joint 1 */
        signed short joint1 = Dynamix.getPosition(01);
        delay(2);
        if (xbee.getEMG_CH1() > 100) {
          Dynamix.setPosition(01, joint1 - 10, 03);
        }
        else if (xbee.getEMG_CH2() > 100) {
          Dynamix.setPosition(01, joint1 + 10, 03);
        }
        break;

      case 1:
        /* joint 2 */
        signed short joint2 = Dynamix.getPosition(02);
        delay(2);
        if (xbee.getEMG_CH1() > 100) {
          Dynamix.setPosition(02, joint2 - 10, 03);
        }
        else if (xbee.getEMG_CH2() > 100) {
          Dynamix.setPosition(02, joint2 + 10, 03);
        }
        break;

      case 2:
        /* joint 3 */
        signed short joint3 = Dynamix.getPosition(03);
        delay(2);
        if (xbee.getEMG_CH1() > 100) {
          Dynamix.setPosition(03, joint3 - 10, 03);
        }
        else if (xbee.getEMG_CH2() > 100) {
          Dynamix.setPosition(03, joint3 + 10, 03);
        }
        break;

      case 3:
        /* gripper */
        signed short gripper = Dynamix.getPosition(4);
        delay(2);
        if (gripper > 3000) {// gripper er open
          Dynamix.setPosition(10, 2000, 03);
        }
        if (gripper < 2800) {// gripper er open
          Dynamix.setPosition(10, 3100, 03);
        }
        break;

      default:
        break;
    }
}
void loop() {
  while (!Serial2) {}
  startup();
  float hertz = 1000 / 20;
  long old_time;
  while (!Serial2) {}
  startup();
  bool runs = false;
  bool runs1 = false;
  while (true) {

    old_time = millis();

    xbee.updateData();

<<<<<<< HEAD


    if (digitalRead(31) == HIGH) {
      /*     value = Dynamix.getPosition(02);
           delay(5);
           Serial.print(value);
           Serial.print(" | ");
           value = value - 20;
           Dynamix.setPosition(02, value, 03);
           delay(10);
           Serial.println(Dynamix.getPosition(02));
           //delay(1);}

           Dynamix.setPosition(01, 3000, 04);
           delay(2);
           Dynamix.setPosition(02, 1600, 04);
           delay(2);
           Dynamix.setPosition(03, 1800, 04);
           delay(2);
           Dynamix.setPosition(10, 2047, 04);
           delay(2);
           // Dynamix.setPosition(05, 2047, 04);
           delay(2);
           Dynamix.setAction(0xFE);
      */
      if (runs == false) {

        Dynamix.inverseKinematics(0.305, 0, -0.02037);
        delay(10);
        Serial.print("kører inverse");
        runs = true;
      }
      delay(2000);

      if (runs1 == false) {

        Dynamix.inverseKinematics(0.305, 0.53, -0.026);
        delay(10);
        Serial.print("kører inverse");
        runs1 = true;
      }
      delay(2000);
      runs1 = false;
      runs = false;

      while (millis() - old_time < hertz);
    }
  }
  //value = Dynamix.getPosition(02);
  /*
    if (digitalRead(31) == HIGH) {
        value = Dynamix.getPosition(02);
        delay(2);
        //Serial.print(value);
        //Serial.print(" | ");
        value =-10;
        Dynamix.setPosition(02, value, 03);
        delay(10);
        //Serial.println(Dynamix.getPosition(02));
    //Serial.println(value);
    }*/


  
    if (!digitalRead(downButton)){
=======
    if (xbee.getAccY() > 600){ // resting is around 560
>>>>>>> 078cf16695f26547c889b803e2755c1c3ffc740f
    menu++;
    y++;
    if (menu>4){
    menu=0;
    y = 0;
    }
    updateMenu();
    moving();
    //delay(50);
    //while (!digitalRead(downButton));
    }
    if (xbee.getAccY() < 500){ // resting is around 560
    menu--;
    y--;
    if (menu<0){
     menu=4;
     y = 4;
    }
    updateMenu();
    moving();
    delay(2);
    //while (!digitalRead(upButton));
    }
    if (xbee.getEMG_CH1() > 100){ // resting is around 0
    execute();
    ///updateMenu();
    delay(2);
    while (!digitalRead(selectButton));
    }
<<<<<<< HEAD
  
=======
      while (millis() - old_time < hertz);
    
  }
  

 
>>>>>>> 078cf16695f26547c889b803e2755c1c3ffc740f
}

#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"
#include "src/libs/Elegoo_TFTLCD/Elegoo_TFTLCD.h"

//////////////////////// Exponetial filter //////////////7
int32_t OUTemgY;
int32_t oldOUTemgY = 0;
int32_t OUTemgCH1;
int32_t oldOUTemgCH1 = 0;
int32_t OUTemgCH2;
int32_t oldOUTemgCH2 = 0;
int weight = 0.8;
#define ACC_Y 1
#define EMG_CH1 2
#define EMG_CH2 3

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
//Det er fordi jeg elskser alle farver...
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

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

int menu = 0;         //menu value for switch
int y = 0;            // variable y koordinate for pointer (arrow)
bool MainMenu = true; // to check which menu the user is in
// Point states which are used to tell whether or not the custom points store coordinates in them (green or red)
bool Point1State = false;
bool Point2State = false;
bool Point3State = false;
bool Point4State = false;
int sensorMin = 1023;                      // almost random number for calibration
int sensorMax = 0;                         // same as above
int sensorValue = 0;                       // accelerometer input
int PointerY[5] = {35, 70, 105, 140, 170}; // array with y coordinates for pointer
int gripperPos = 0;                        // 0=open, 1=closed

int32_t val1 = 0;
int32_t val2 = 0;

//arrays for pointMenu for getPos
int32_t arrPoint1[3];
int32_t arrPoint2[3];
int32_t arrPoint3[3];
int32_t arrPoint4[3];

void setup()
{
  Serial.begin(9600);
  xbee.begin(Serial1, 115200);
  Dynamix.begin(Serial2, 57600, DIRECTION_PIN);
  delay(1000);
  while (!Serial2)
  {
  }
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
  Dynamix.setPosition(JOINT_2, 3073, REQ_WRITE);
  //Dynamix.setPosition(JOINT_2, 2500, REQ_WRITE);// brugt til test - skal slettes
  Dynamix.setPosition(JOINT_3, 2047, REQ_WRITE);
  Dynamix.setPosition(GRIPPER_BOTH, 2047, REQ_WRITE);
  delay(2);
  Dynamix.setAction(0xFE);
  delay(2000);

  tft.reset();           // reset the display
  tft.begin(0x9341);     // start communication with the display on given address
  tft.fillScreen(BLACK); //fill whole screen with color black (not required, but then the screen will flash with grey colors)
  updateMenu();          // updating the switch menu state
}
//Print main menu . Only text here
void PrintMainMenu()
{
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(70, 35);
  tft.print(" Joint 1 ");
  tft.setCursor(70, 70);
  tft.print(" Joint 2 ");
  tft.setCursor(70, 105);
  tft.print(" Joint 3 ");
  tft.setCursor(70, 140);
  tft.print(" Gripper ");
  tft.setCursor(70, 175);
  tft.print(" Points ");
}
//Print sub menu, but validate the pointStates first and color them with corresponding color
void PrintSubMenu()
{
  if (Point1State == true)
  {
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(70, 35);
    tft.print(" Point 1 ");
  }
  else
  {
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(70, 35);
    tft.print(" Point 1 ");
  }
  if (Point2State == true)
  {
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(70, 70);
    tft.print(" Point 2 ");
  }
  else
  {
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(70, 70);
    tft.print(" Point 2 ");
  }
  if (Point3State == true)
  {
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(70, 105);
    tft.print(" Point 3 ");
  }
  else
  {
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(70, 105);
    tft.print(" Point 3 ");
  }
  if (Point4State == true)
  {
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.setCursor(70, 140);
    tft.print(" Point 4 ");
  }
  else
  {
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(70, 140);
    tft.print(" Point 4 ");
  }
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(70, 175);
  tft.print(" Back<- ");
}

//Print Pointer
void printPointer()
{
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(40, PointerY[y]);
  tft.print("->");
}

void startup()
{
  for (int i = 0; i < 10; i++)
  {
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

// Function that refreshes the column with the pointer, and prints the pointer at the new place after each iteration
void updateMenu()
{
  if (MainMenu == true)
  { 
    PrintMainMenu();
  }
  switch (menu)
  {
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
// execute function that checks if the user is in the sub menu, where it will change the point state from false to true for each
//corresponding case, and prints (updates) the submenu again
void execute()
{
  switch (menu)
  {
  if (MainMenu == false){
  case 0:
      Point1State = true;
      PrintSubMenu();
    break;
  case 1:
      Point2State = true;
      PrintSubMenu();
    break;

  case 2:
      Point3State = true;
      PrintSubMenu();
    break;

  case 3:
      Point4State = true;
      PrintSubMenu();
    break;
  }

  case 4:
    tft.fillScreen(BLACK);
    if (MainMenu == true)
    {
      PrintSubMenu();
      MainMenu = false;
      printPointer();
    }
    else
    {
      tft.fillScreen(BLACK);
      PrintMainMenu();
      MainMenu = true;
      printPointer();
    }
    break;
  }
}
// Each case waits for the input from either EMG channel 1 or channel 2, where the former will get the position of each
//dynamixel motor and then insert that data in corresponding array, while the latter will read data from aforementioned arrays
// and send data as position commands to the dynamixel motors
void runPoint()
{
  xbee.updateData();
  switch (menu)
  {
  case 0:
    if (xbee.getEMG_CH1() > 200)
    {
      arrPoint1[0] = Dynamix.getPosition(JOINT_1);
      delay(6);
      arrPoint1[1] = Dynamix.getPosition(JOINT_2);
      delay(6);
      arrPoint1[2] = Dynamix.getPosition(JOINT_3);

      for (int i = 0; i < 3; i++)
      {
        Serial.print(arrPoint1[i]);
        Serial.print(" ");
      }
      Serial.println();
    }
    else if (xbee.getEMG_CH2() > 200)
    {
      Dynamix.setPosition(JOINT_1, arrPoint1[0], REQ_WRITE);
      Dynamix.setPosition(JOINT_2, arrPoint1[1], REQ_WRITE);
      Dynamix.setPosition(JOINT_3, arrPoint1[2], REQ_WRITE);
      Dynamix.setAction(0xfe);
    }
    break;

  case 1:
    if (xbee.getEMG_CH1() > 200)
    {
      arrPoint2[0] = Dynamix.getPosition(JOINT_1);
      delay(6);
      arrPoint2[1] = Dynamix.getPosition(JOINT_2);
      delay(6);
      arrPoint2[2] = Dynamix.getPosition(JOINT_3);
    }
    else if (xbee.getEMG_CH2() > 200)
    {
      Dynamix.setPosition(JOINT_1, arrPoint2[0], REQ_WRITE);
      Dynamix.setPosition(JOINT_2, arrPoint2[1], REQ_WRITE);
      Dynamix.setPosition(JOINT_3, arrPoint2[2], REQ_WRITE);
      Dynamix.setAction(0xfe);
    }
    break;

  case 2:
    if (xbee.getEMG_CH1() > 200)
    {
      arrPoint3[0] = Dynamix.getPosition(JOINT_1);
      delay(6);
      arrPoint3[1] = Dynamix.getPosition(JOINT_2);
      delay(6);
      arrPoint3[2] = Dynamix.getPosition(JOINT_3);
    }
    else if (xbee.getEMG_CH2() > 200)
    {
      Dynamix.setPosition(JOINT_1, arrPoint3[0], REQ_WRITE);
      Dynamix.setPosition(JOINT_2, arrPoint3[1], REQ_WRITE);
      Dynamix.setPosition(JOINT_3, arrPoint3[2], REQ_WRITE);
      Dynamix.setAction(0xfe);
    }

    break;

  case 3:
    if (xbee.getEMG_CH1() > 200)
    {
      arrPoint4[0] = Dynamix.getPosition(JOINT_1);
      delay(6);
      arrPoint4[1] = Dynamix.getPosition(JOINT_2);
      delay(6);
      arrPoint4[2] = Dynamix.getPosition(JOINT_3);
    }
    else if (xbee.getEMG_CH2() > 200)
    {
      Dynamix.setPosition(JOINT_1, arrPoint4[0], REQ_WRITE);
      Dynamix.setPosition(JOINT_2, arrPoint4[1], REQ_WRITE);
      Dynamix.setPosition(JOINT_3, arrPoint4[2], REQ_WRITE);
      Dynamix.setAction(0xfe);
    }
    break;

  default:
    break;
  }
}
// Function for converting EMG signal into boolean
int XbeeMeter(double currentstate)
{
  xbee.updateData();
  if (currentstate > 650)
  {
    return 1;
  }

  if (currentstate < 320)
  {
    return -1;
  }

  else
  {
    return 0;
  }
}

int32_t expoentialFilter(int type)
{
  xbee.updateData();
  delay(1);
  if (type == ACC_Y)
  {
    OUTemgY = (weight * xbee.getAccY()) + ((1 - weight) * oldOUTemgY);
    oldOUTemgY = OUTemgY;
    return OUTemgY;
  }

  else if (type == EMG_CH1)
  {
    //Serial.print("old ch1: ");
    //Serial.println(oldOUTemgCH1);
    OUTemgCH1 = (weight * xbee.getEMG_CH1()) + ((1 - weight) * oldOUTemgCH1);
    oldOUTemgCH1 = OUTemgCH1;
    //Serial.print("new ch1: ");
    //Serial.println(OUTemgCH1);
    return OUTemgCH1;
  }

  else if (type == EMG_CH2)
  {
    OUTemgCH2 = weight * xbee.getEMG_CH2() + (1 - weight) * oldOUTemgCH2;
    oldOUTemgCH2 = OUTemgCH2;
    Serial.print("new ch2: ");
    Serial.println(OUTemgCH2);
    return OUTemgCH1;
    return OUTemgCH2;
  }
}

void PrimeMover(int a)
{
  const char Limb[4] = {JOINT_1, JOINT_2, JOINT_3};
  int32_t joint = Dynamix.getPosition(Limb[a]);
  int32_t sendjointN = joint - 40;
  int32_t sendjointP = joint + 40;
  delay(6);
  // val1 = expoentialFilter(EMG_CH1); // calculate the exponetial filter value
  // val2 = expoentialFilter(EMG_CH2); // calculate the exponetial filter value
  val1 = xbee.getEMG_CH1(); //xbee.getEMG_CH1();
  val2 = xbee.getEMG_CH2(); //xbee.getEMG_CH2();
                            //Serial.print("ch1: ");
  //Serial.println(val1);
  //Serial.print("ch2: ");
  //Serial.println(val2);

  if (val1 > 200)
  {
    if (a == 0 || a == 1 || a == 2)
    {
      joint = Dynamix.getPosition(Limb[a]);
      sendjointN = joint - 40;
      delay(6);
      Dynamix.setPosition(Limb[a], sendjointN, WRITE);
      delay(6);
      val1 = expoentialFilter(EMG_CH1);
    }
    else if (a == 3)
    {
      joint = Dynamix.getPosition(GRIPPER_LEFT);
      sendjointN = joint - 40;
      delay(6);
      Dynamix.setPosition(GRIPPER_BOTH, sendjointN, WRITE);
      delay(6);
      val1 = expoentialFilter(EMG_CH1);
    }
  }

  else if (val2 > 300)
  {
    if (a == 0 || a == 1 || a == 2)
    {
      joint = Dynamix.getPosition(Limb[a]);
      sendjointP = joint + 40;
      delay(6);
      Dynamix.setPosition(Limb[a], sendjointP, WRITE);
      delay(6);
      val2 = expoentialFilter(EMG_CH2);
    }
    else if (a == 3)
    {
      joint = Dynamix.getPosition(GRIPPER_LEFT);
      sendjointN = joint + 40;
      delay(6);
      Dynamix.setPosition(GRIPPER_BOTH, sendjointP, WRITE);
      delay(6);
      val2 = expoentialFilter(EMG_CH2);
    }
  }

  else
  {
    Dynamix.clearSerialBuffer();
  }
}

double tracvia(double theta0, double thetag, double thetav, double tf, double t)
{

  double a10 = theta0;
  double a11 = 0;
  double a12 = ((12 * thetav) - (3 * thetag) - (9 * theta0)) / (4 * (tf * tf));
  double a13 = ((-8 * thetav) + (3 * thetag) + (5 * theta0)) / (4 * (tf * tf * tf));

  double th1 = a12 * (t * t) + a13 * (t * t * t);

  double a20 = thetav;

  double a21 = ((3 * thetag) - (3 * theta0)) / (4 * (tf));
  double a22 = ((-12 * thetav) + (6 * thetag) + (6 * theta0)) / (4 * (tf * tf));
  double a23 = ((8 * thetav) - (5 * thetag) - (3 * theta0)) / (4 * (tf * tf * tf));

  double thetas = a10 + a12 * (t * t) + a13 * (t * t * t);
  double thetaf = a20 + a21 * t + a22 * (t * t) + a23 * (t * t * t);
}

void loop()
{
  while (!Serial2)
  {
  }
  startup();
  float hertz = 1000 / 1000;
  long old_time;
  int starttime;

  while (true)
  {
    old_time = millis();
    xbee.updateData();

    if (XbeeMeter(xbee.getAccY()) == 1)
    {
      menu++;
      y++;
      if (menu > 4)
      {
        menu = 0;
        y = 0;
      }
      updateMenu();

      starttime = millis();
      delay(1000);
      //  while (XbeeMeter(xbee.getAccY())==1){
      //    if (millis() > starttime + 2000)
      //    {
      //      break;
      //    }

      //  }
    }

    if (XbeeMeter(xbee.getAccY()) == -1)
    { // resting is around 560
      menu--;
      y--;
      if (menu < 0)
      {
        menu = 4;
        y = 4;
      }
      updateMenu();

      delay(2);
      starttime = millis();
      delay(1000);
      //   while (XbeeMeter(xbee.getAccY())==-1){
      //    if (millis() > starttime + 2000)
      //    {
      //      break;
      //    }
      //  }
    }
    if (menu == 4 || MainMenu == false)
    {
      if (xbee.getEMG_CH1() > 200)
      {
        execute();
        //updateMenu();
        delay(2);
      }
    }
    if (MainMenu == true)
    {
      PrimeMover(menu);
    }
    if (MainMenu == false)
    {
      runPoint();
    }

    Serial.println(menu);
    //while (millis() - old_time < hertz);
  }
}

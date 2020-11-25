#include "src/libs/EMG_Lib/EMG.h"
#include "src/libs/IntervalTimer/IntervalTimer.h"
#include "src/libs/Dynamixel_Lib/Dynamixel.h"
#include "src/libs/EMG_menu/EMG_menu.h"

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
//EMGmenu menuClass;
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
int PointerY[5]={35,70,105,140,170}; // array with y coordinates for pointer


void setup() {
  pinMode(31, INPUT);
  Serial.begin(9600);
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

//Print Pointer
  void printPointer(){
    tft.setCursor(40,PointerY[y]);
    tft.print("->");
  }

void startup() {
  for (int i = 0; i < 10; i++) {
    Dynamix.getPosition(02);
    delay(10);
  }
}
bool moving= false;

  // the menu, where only pointer moves
  void updateMenu(){
    if (MainMenu == true){  // prints the main menu IF the user IS in the main menu 
    tft.PrintMainMenu();  
    };
    switch (menu){
    case 0:
    tft.fillRect(40,0,33,240,BLACK);
    tft.printPointer(y);
    break;
    case 1:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer(y);
    break;
    case 2:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer(y);

    break;
    case 3:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer(y);
    
    break;
    case 4:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer(y);
    
    break;
    }
  }

  void execute() {  //the "select" function
  switch (menu) {
    case 0:
    if (MainMenu == false){ //cheks if the user is in the main menu
      
      if(Point1State == false){ // checks wheter or not the points "store" coordinates in them
      tft.setTextColor(RED);  tft.setTextSize(3); //sets the color, text size and the coordinates for the text location
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 1 "); //prints text to the screen, where "0" is ordinary print and "1" is println
      Point1State = true; 
      } 
      else if(Point1State == true){
      tft.setTextColor(GREEN);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 1 ");
      Point1State = false;
      }
    }
      break;
    case 1:
    if (MainMenu == false){
      
      if(Point2State == false){
      tft.setTextColor(RED);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 2 ");
      Point2State = true; 
      } 
      else if(Point2State == true){
      tft.setTextColor(GREEN);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 2 ");
      Point2State = false;
      }
    }
      break;

    case 2:
    if (MainMenu == false){
      
      if(Point3State == false){
      tft.setTextColor(RED);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 3 ");
      Point3State = true;
      }
      else if(Point3State == true){
      tft.setTextColor(GREEN);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 3 ");
      Point3State = false; 
      }
    }
      break;

    case 3:
    if (MainMenu == false){
      
      if(Point4State == false){
      tft.setTextColor(RED);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 4 ");
      Point4State = true;
      } 
      else if(Point4State == true){
      tft.setTextColor(GREEN);  tft.setTextSize(3);
      tft.setCursor(70,PointerY[y]);
      tft.print(" Point 4 ");
      Point4State = false;
      }
    }
      break;
    case 4:
    tft.fillScreen(BLACK);
    if(MainMenu == true){
    PrintSubMenu();
    MainMenu = false;  
    }
    else{
    tft.fillScreen(BLACK);
    tft.PrintMainMenu();
    MainMenu = true;
    }
      break;
  }
}
void callibration(){ //not actually used yet
    while (millis() < 5000) 
    {
    tft.setTextColor(GREEN);  tft.setTextSize(2);
    tft.setCursor(70,PointerY[y]);
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
    tft.setCursor(70,PointerY[y]);
    tft.print(sensorValue);
    }
}
void loop() {
  while (!Serial2) {}
  startup();
  value = Dynamix.getPosition(02);
 //Serial.println(value);

    realValue = value + 100;


    //delay(2);
    Dynamix.setPosition(02, 3000, 03); 
    //delay(1);
    Serial.println("reg_write1");
    //delay(1000);
    Dynamix.setAction(02);
    //delay(1);
    moving = Dynamix.getMoving(02);
    while(moving==true){
      moving = Dynamix.getMoving(02);
      //delay(2);
      Serial.println("moving1");}
      
    //delay(2);
    Dynamix.setPosition(02, 1000, 03); 
    //delay(1);
    Serial.println("reg_write2");
    //delay(1000);
    Dynamix.setAction(02);
    //delay(1);
   while(moving==true){
      moving = Dynamix.getMoving(02);
      //delay(2);
      Serial.println("moving2");
    }

    if (!digitalRead(downButton)){
    menu++;
    y++;
    if (menu>4){
     menu=0;
     y = 0;
    }
    updateMenu();
    delay(50);
    //while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    y--;
    if (menu<0){
      menu=4;
      y = 4;
    }
    updateMenu();
    delay(50);
    //while (!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    execute();
    ///updateMenu();
    delay(50);
    while (!digitalRead(selectButton));
  }
}

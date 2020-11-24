#include <EMG.h>
#include <Elegoo_TFTLCD.h>
#include <Elegoo_GFX.h>

//declaration of used analog pins on arduino
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

EMGclass xbee;

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

  int upButton = 52;
  int downButton = 53;
  int selectButton = 51;
  int menu = 0;
  int y = 0;    
  //coordinates for pointer cursor                                            
  int PointerY[5]={35,70,105,140,170};
  bool MainMenu = true;
  bool PointState = false;
  int sensorMin = 1023; 
  int sensorMax = 0;
  int sensorValue = 0;


void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  tft.fillScreen(BLACK);
  updateMenu();
  
}

//Print main menu
  void PrintMainMenu(){
    tft.setTextColor(WHITE);  tft.setTextSize(3);
    tft.setCursor(70,35);
    tft.print(" Joint 1 ");
    tft.setCursor(70,70);
    tft.print(" Joint 2 ");
    tft.setCursor(70,105);
    tft.print(" Joint 3 ");
    tft.setCursor(70,140);
    tft.print(" Gripper " );
    tft.setCursor(70,175);
    tft.print(" Points ");
  }
//Print sub menu
  void PrintSubMenu(){
    //tft.setCursor(0,0);
    tft.println();
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70,35);
    tft.print(" Point 1 ");
    tft.setCursor(70,70);
    tft.print(" Point 2 ");
    tft.setCursor(70,105);
    tft.print(" Point 3 ");
    tft.setCursor(70,140);
    tft.print(" Point 4 ");
    tft.setCursor(70,175);
    tft.print(" Back ");
  }

//Print Pointer
  void printPointer(){
    tft.setCursor(40,PointerY[y]);
    tft.print("->");
  }
      
  void updateMenu(){
    if (MainMenu == true){
    PrintMainMenu();  
    };
    switch (menu){
    case 0:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer();
    break;
    case 1:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer();
    break;
    case 2:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer();

    break;
    case 3:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer();
    
    break;
    case 4:
    tft.fillRect(40,0,33,240,BLACK);
    printPointer();
    
    break;
  }
}
void execute() {
  switch (menu) {
    case 0:
    if (MainMenu == false){
      
      if(PointState == false){
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 1 ");
    PointState = true; 
      } 
      else if(PointState == true){
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 1 ");
    PointState = false;
      }
    }
      break;
    case 1:
    if (MainMenu == false){
      
      if(PointState == false){
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 2 ");
    PointState = true; 
      } 
      else if(PointState == true){
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 2 ");
    PointState = false;
      }
    }
      break;

    case 2:
    if (MainMenu == false){
      
      if(PointState == false){
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 3 ");
    PointState = true;
      }
      else if(PointState == true){
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 3 ");
    PointState = false; 
      }
    }
      break;

    case 3:
    if (MainMenu == false){
      
      if(PointState == false){
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 4 ");
    PointState = true; 
      } 
      else if(PointState == true){
    tft.setTextColor(GREEN);  tft.setTextSize(3);
    tft.setCursor(70,PointerY[y]);
    tft.print(" Point 4 ");
    PointState = false;
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
    PrintMainMenu();
    MainMenu = true;
    }
      break;
  }
}
void loop() {
  if (!digitalRead(downButton)){
    menu++;
       y++;
     if (menu>4){
       menu=0;
       y = 0;
    }
    updateMenu();
    delay(200);
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
    delay(200);
    //while (!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    execute();
    ///updateMenu();
    delay(200);
    while (!digitalRead(selectButton));
  }
  // calibrate during the first five seconds
  while (millis() < 5000) {
    xbee.updateData();
    sensorValue = xbee.getAccX();
    // record the maximum sensor value
    if (sensorValue > sensorMax) {
    sensorMax = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorMin) {
    sensorMin = sensorValue;
    }
  }
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

}

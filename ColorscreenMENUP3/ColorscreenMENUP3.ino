//#include "src/libs/Elegoo_TFTLCD/Elegoo_TFTLCD.h"
#include "Elegoo_TFTLCD.h"
//#include <Elegoo_GFX.h>

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

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

  int upButton = 52;
  int downButton = 53;
  int menu = 0;


void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  updateMenu();
  
}
void loop() {
  if (!digitalRead(downButton)){
    menu++;
        if (menu>5){
      menu=0;
    }
    updateMenu();
    delay(200);
    //while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    if (menu<0){
      menu=5;
    }
    updateMenu();
    delay(200);
    //while (!digitalRead(upButton));
  }
}
  void updateMenu(){
  switch (menu){
    case 0:
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.fillRect(3, 0, 2, 240, WHITE);
    tft.fillRect(5, 0, 4, 40, WHITE);
    tft.fillRect(9, 0, 2, 240, WHITE);
    tft.setCursor(0,0);
    tft.println();
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.println(" ->Joint 1 ");
    tft.println();
    tft.println(" Joint 2 ");
    tft.println();
    tft.println(" Joint 3 ");
    tft.println();
    tft.println(" Gripper ");
    break;
    case 1:
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.fillRect(3, 0, 2, 240, WHITE);
    tft.fillRect(5, 40, 4, 40, WHITE);
    tft.fillRect(9, 0, 2, 240, WHITE);
    tft.setCursor(0,0);
    tft.println();
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.println(" Joint 1 ");
    tft.println();
    tft.println(" ->Joint 2 ");
    tft.println();
    tft.println(" Joint 3 ");
    tft.println();
    tft.println(" Gripper ");
    break;
    case 2:
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.fillRect(3, 0, 2, 240, WHITE);
    tft.fillRect(5, 80, 4, 40, WHITE);
    tft.fillRect(9, 0, 2, 240, WHITE);
    tft.setCursor(0,0);
    tft.println();
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.println(" Joint 2");
    tft.println();
    tft.println(" ->Joint 3");
    tft.println();
    tft.println(" Gripper");
    tft.println();
    tft.println(" Return P2");
    break;
    case 3:
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.fillRect(3, 0, 2, 240, WHITE);
    tft.fillRect(5, 120, 4, 40, WHITE);
    tft.fillRect(9, 0, 2, 240, WHITE);
    tft.setCursor(0,10);
    tft.println();
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.println(" Joint 3");
    tft.println();
    tft.println(" ->Gripper");
    tft.println();
    tft.println(" Return P2");
    tft.println();
    tft.println(" Return P2");
    break;
    case 4:
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.fillRect(3, 0, 2, 240, WHITE);
    tft.fillRect(5, 160, 4, 40, WHITE);
    tft.fillRect(9, 0, 2, 240, WHITE);
    tft.setCursor(0,10);
    tft.println();
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.println(" Joint 3");
    tft.println();
    tft.println(" Gripper");
    tft.println();
    tft.println(" ->Return P1");
    tft.println();
    tft.println(" Return P2");
    break;
    case 5:
    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.fillRect(3, 0, 2, 240, WHITE);
    tft.fillRect(5, 200, 4, 40, WHITE);
    tft.fillRect(9, 0, 2, 240, WHITE);
    tft.setCursor(0,10);
    tft.println();
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.println(" Joint 3");
    tft.println();
    tft.println(" Gripper");
    tft.println();
    tft.println(" Return P1");
    tft.println();
    tft.println(" ->Return P2");
    break;
  }
}

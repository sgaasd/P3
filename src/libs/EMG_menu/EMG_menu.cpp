#include "EMG_menu.h"

//Det er fordi jeg elskser alle farver...
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
/*
//Print main menu
  void EMGmenu::PrintMainMenu(){
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

  void EMGmenu::PrintSubMenu(){
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

  void EMGmenu::SetParam(int color, int size, int x, int y){
    tft.setTextColor(color);  tft.setTextSize(size);
    tft.setCursor(x,y);
  }

  void EMGmenu::print(String text, int type){
    if (type == 0)
    {
      tft.print(text);
    }
    else if (type == 1)
    {
      tft.println(text);
    }
    else if (type != 1 && type !=  2)
    {
      tft.print("error in type input");
    }
    
    
  }
  void EMGmenu::reset(){
    tft.reset();
  }

  void EMGmenu::begin(int addr){
    tft.begin(addr);
  }

  void EMGmenu::fillScreen(int color){
    tft.fillScreen(color);
  }
  void EMGmenu::fillRect(int x,int y,int width,int height, int color){
    tft.fillRect(x,y,width,height,color);
  }
  */
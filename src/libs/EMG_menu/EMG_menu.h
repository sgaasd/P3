#pragma once
#include "Elegoo_TFTLCD/Elegoo_TFTLCD.h"


//declaration of used analog pins on arduino

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4



class EMGmenu
{
private:
//coordinates for pointer cursor                                            
int PointerY[5]={35,70,105,140,170}; // array with y coordinates for pointer

    
public:
    void PrintMainMenu();
    void PrintSubMenu();
    void SetParam(int color, int size, int x, int y);
    void print(String text, int type);
    //void print(int value, int type);
    void reset();
    void begin(int addr);
    void fillScreen(int color);
    void fillRect(int x,int y,int width,int height, int color);
    void printPointer(int y);
};


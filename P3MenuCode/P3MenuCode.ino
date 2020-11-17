#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Telling I2C module the adress of the LCD dispaly, where 0x27 is the adress (which can be different), and then 16 collumns and 4 rows.
LiquidCrystal_I2C lcd(0x27,16,4);

//special characters in vectorform (binary code would also work)
 uint8_t arrow[8] = {0x00,0x04,0x06,0x1f,0x06,0x04,0x00,0x00};
 uint8_t reversearrow[7] = {0x00,0x04,0x0c,0x1f,0x0c,0x04,0x00};

  int upButton = 10;
  int downButton = 11;
  int menu = 0;


void setup() {
  //start screen
  lcd.begin();
  //lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  //create special characters
  lcd.createChar(0,arrow);
  lcd.createChar(1,reversearrow);
  //idk what this is 
  lcd.home();
  //function for menu screen
  updateMenu();
  

  //clean the screen
  lcd.clear();
  //set cursor to these cooridnates
  lcd.setCursor(0,0);
  //draw arrow
  lcd.write(0);  
  //print text
  lcd.print(" ROBOTICS P3 ");
  //draw arrow
  lcd.write(1);
  //set cursor to these coordinates
  lcd.setCursor(0,2);  
  //print test
  lcd.print(" Group 360 ");
  //wait 3 sec
  delay(3000);
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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write(0);
    lcd.print(" Joint 1 ");
    lcd.write(1);
    lcd.setCursor(0,1);
    lcd.print(" Joint 2 ");
    lcd.setCursor(-4,2);
    lcd.print(" Joint 3 ");
    lcd.setCursor(-4,3);
    lcd.print(" Gripper ");
    break;
    case 1:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Joint 1 ");
    lcd.setCursor(0,1);
    lcd.write(0);
    lcd.print(" Joint 2 ");
    lcd.write(1);
    lcd.setCursor(-4,2);
    lcd.print(" Joint 3 ");
    lcd.setCursor(-4,3);
    lcd.print(" Gripper ");
    break;
    case 2:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Joint 2 ");
    lcd.setCursor(0,1);
    lcd.write(0);
    lcd.print(" Joint 3 ");
    lcd.write(1);
    lcd.setCursor(-4,2);
    lcd.print(" Gripper ");
    lcd.setCursor(-4,3);
    lcd.print(" Return point 1 ");
    break;
    case 3:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Joint 3 ");
    lcd.setCursor(0,1);
    lcd.write(0);
    lcd.print(" Gripper ");
    lcd.write(1);
    lcd.setCursor(-4,2);
    lcd.print(" Return point 1 ");
    lcd.setCursor(-4,3);
    lcd.print(" Return point 2 ");
    break;
    case 4:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Joint 3 ");
    lcd.setCursor(0,1);
    lcd.print(" Gripper ");
    lcd.setCursor(-4,2);
    lcd.write(0);
    lcd.print(" Return point 1 ");
    lcd.setCursor(-4,3);
    lcd.print(" Return point 2 ");
    break;
    case 5:
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Joint 3 ");
    lcd.setCursor(0,1);
    lcd.print(" Gripper ");
    lcd.setCursor(-4,2);
    lcd.print(" Return point 1 ");
    lcd.setCursor(-4,3);
    lcd.write(0);
    lcd.print(" Return point 2 ");
    lcd.write(1);
    break;
  }
}

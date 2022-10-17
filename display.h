 
#include "LiquidCrystal_I2C.h"

extern volatile uint32_t Freq;

LiquidCrystal_I2C lcd(0x27,40,2);  //set the LCD address to 0x27(PCF8574T)

void displayInit()
{
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
}

void displayFreq()
{
   lcd.print(Freq);
}


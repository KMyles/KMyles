 
#include "LiquidCrystal_I2C.h"  //need the glue for the display

extern volatile uint32_t Freq;  //tell the display.h file that the freq is outside of its file 

LiquidCrystal_I2C lcd(0x27,40,2);  //set the LCD address to 0x27(PCF8574T) //set up the LCD object

void displayInit()
{
    lcd.init();                      // initialize the lcd 
    lcd.backlight();                 //turn on the backlight 
}

void displayFreq()
{
   lcd.print(Freq);                 //Display the global VAriable Freq
}


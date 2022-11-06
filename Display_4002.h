#include "LiquidCrystal_I2C.h"

extern volatile uint32_t freq;
extern int step;

LiquidCrystal_I2C lcd(0x27,40,2);  //set the LCD address to 0x27(PCF8574T)

void InitDisplay()
{
 lcd.init();                      
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("40m LSB 2.3kHz");
 lcd.setCursor(20,0);
 lcd.print(freq);
}

void DisplayFreq()
{
 lcd.setCursor(20,0);
 lcd.print(freq);
  
}

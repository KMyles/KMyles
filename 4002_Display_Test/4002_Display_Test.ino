
///SDA pin to pin 18 on  Teensy 4.0/4.1 
///SCL pinn to pin 19 on Teensy 4.0/4.1
/// VSS to Teensy Gnd
///VDD to teensy 5V


#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,40,2);  //set the LCD address to 0x27(PCF8574T)

void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop()
{
}

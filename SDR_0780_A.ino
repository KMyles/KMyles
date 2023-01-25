#include "font_Arial.h"
#include "ER-TFT0784_t3.h"

// Pin connection mapping
ER_TFT0784_t3 tft = ER_TFT0784_t3(
// Teensy pin  // Display        pin
    10,        // RA8876 CS      5
     6,        // RA8876 RESET   11
    11,        // RA8876 MOSI    7
    13,        // RA8876 SCLK    8
    12,        // RA8876 MISO    6
    3,        // SSD2828 CS     31
    5 ,        // SSD2828 RESET  43
    2,         // SSD2828 SDI    34
    4         // SSD2828 SCK    35
);
//External backlight control connected to this Arduino pin
#define BACKLIGHT 9 // Display pin: 14

// Array of Simple RA8876 Basic Colors
PROGMEM uint16_t myColors[] = {
  0x0000,
  0xffff,
  0xf800,
  0xfc10,
  0x8000,
  0x07e0,
  0x87f0,
  0x0400,
  0x001f,
  0x051f,
  0x841f,                   
  0x0010,
  0xffe0,
  0xfff0,
  0x8400,
  0x07ff,
  0x87ff,
  0x0410,
  0xf81f,
  0xfc1f,
  0x8010,
  0xA145
};


void setup() {
  pinMode(BACKLIGHT, OUTPUT);
  analogWriteFrequency(BACKLIGHT,50000);
  analogWrite(BACKLIGHT, 128);
 
  tft.begin(20000000);
  tft.setRotation(1);
  tft.graphicMode(true);
  tft.setFont(Arial_32);
  tft.fillScreen(BLACK);
  tft.setTextColor(myColors[5]);
  tft.setCursor(500,15);
  tft.print("14.125000 MHz");
  tft.drawLine(0,70,1280,70
  ,WHITE);
  tft.drawLine(0,325,1280,325,WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:

}

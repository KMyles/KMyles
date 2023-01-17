
#include <SPI.h>
#include <ILI9488_t3.h>
#include "ili9488_t3_font_Arial.h"
#include "ili9488_t3_font_ArialBold.h"

#include <analyze_fft256_iq_F32.h>

extern volatile uint32_t Frequency;

extern volatile uint32_t Step ; // sets the tuning increment


////////////////////Define pin connections for TFT and touch (TS) teensy4.0
#define TFT_RESET 14      //Device RESET display
#define TFT_DC    9      //Device Connect display
#define TFT_CS    10     //Chip Select display
//        mosi    11
//        miso    12
//        sck     13

ILI9488_t3 tft=ILI9488_t3(TFT_CS, TFT_DC,TFT_RESET);

DMAMEM RAFB tft_frame_buffer[480 * 320];

void initDisplay()
{
  tft.begin(50000000);
  tft.setRotation(1);
  tft.setFrameBuffer(tft_frame_buffer);
  tft.useFrameBuffer(true);
  tft.fillScreen(ILI9488_BLACK);
  tft.setFont(Arial_14);
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(308, 5);
  tft.drawLine(240,220,240,320,ILI9488_CYAN);
  tft.updateScreenAsync(true);
}

void displayFrequency()
{
  tft.fillRect(290, 0, 189, 35,ILI9488_BLACK);
  tft.setFont(Arial_24);
  tft.setCursor(308, 5);
  tft.setTextColor(ILI9488_ORANGE);
  tft.print(float(Frequency)/1000,3);
  tft.updateScreenAsync();
}








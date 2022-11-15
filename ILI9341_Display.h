
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <ili9341_t3n_font_Arial.h>
#include <ili9341_t3n_font_ArialBold.h>
#include <ILI9341_t3n.h>


////////////////////Define pin connections for TFT and touch (TS) teensy4.0
#define TFT_RESET 8    //Device RESET display
#define TFT_DC    9      //Device Connect display
#define TFT_CS    10     //Chip Select display
//        mosi    11
//        miso    12
//        sck     13
ILI9341_t3n tft=ILI9341_t3n(TFT_CS, TFT_DC);
DMAMEM uint16_t fb1[ILI9341_TFTWIDTH * ILI9341_TFTHEIGHT];

//////////////////////////////////////////////////////////////////////////
extern volatile uint32_t Freq ; // frequency
extern volatile uint32_t Step ; // sets the tuning increment
//////////////////////////////////////////////////////////////////////////
extern int xlF;
extern int filterCenter;
extern int xlB;
extern int filterBandwidth;
/////////////////////////////////////////////////////////////////////////void initTouch();
extern String Mode;
extern float sLevel;
//////////////////////////////////////////////////////////////////////////
void initTemplate()
{
  tft.begin(30000000);
  tft.setRotation(1);
  tft.setFrameBuffer(fb1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setFont(Arial_12_Bold);
  tft.setCursor(8,35);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("S-Meter-");
  tft.updateScreenAsync();
  //tft.drawLine(0,35,480,35,ILI9341_WHITE);
  tft.drawLine(0,60,480,60,ILI9341_CYAN);
 /////////////////////////////GRID//////////////////////////////////
 // tft.drawLine(54,0,54,240,ILI9341_CYAN);
 // tft.drawLine(107,0,107,240,ILI9341_CYAN);
 // tft.drawLine(160,0,160,240,ILI9341_GREEN);
 
 // tft.drawLine(213,0,213,240,ILI9341_CYAN);
 // tft.drawLine(266,0,266,240,ILI9341_CYAN);
  
  tft.drawLine(0,165,320,165,ILI9341_CYAN);
  ////////////////////////SELECT MODE/////////////////////////////////////
  tft.fillRoundRect(0, 210,320,30, 6, ILI9341_BLUE);
 
  tft.setFont(Arial_12_Bold);
  tft.setCursor(11, 218);
  tft.print("CW");
  tft.setCursor(64, 218);
  tft.print("LSB");
  tft.setCursor(116, 218);
  tft.print("USB");
  tft.setCursor(168, 218);
  tft.print("1kHz");
  tft.setCursor(216, 218);
  tft.print("100Hz");
  tft.setCursor(278, 218);
  tft.print("1Hz");
  ///////////////////////////DISPLAY FILTER/////////////////////////////////////////
  tft.setCursor(8, 180);
  tft.print("Filter FC: ");
  tft.setCursor(168, 180);
  tft.print("Filter BW: ");
}

/////////////////////////////Display Frequency///////////////////////////////////////////
void displayFreq()
{ 
  tft.useFrameBuffer(0);
  tft.setFont(Arial_18_Bold);
  tft.fillRect(95, 5, 125, 25,ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(100,7);
  tft.print(float(Freq)/1000,3);
  tft.updateScreenAsync();
}

////////////////////////////Display Mode////////////////////////////////////////
void displayMode()
{
  tft.setFont(Arial_14_Bold);
  tft.fillRect(0, 5, 54, 23,ILI9341_BLACK);
 
  tft.setCursor(10,8);
  tft.setTextColor(ILI9341_WHITE);
  tft.print(Mode);
}

//////////////////////////////////////////////////////////////////////////

void displayTs()
{
  tft.setFont(Arial_12_Bold);
  tft.fillRect(225, 5, 95, 25,ILI9341_BLACK);
  
  tft.setCursor(230,10);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("TS:"+String(Step)+" Hz");
}

/////////////////////////////Display Center Frequency////////////////////////////////////////////////
void displayFc()
{
 tft.setFont(Arial_12_Bold);

tft.useFrameBuffer(0);
tft.fillRect(80,176,80,20,ILI9341_BLACK);//erase bar

tft.setCursor(82,180);
tft.setTextColor(ILI9341_WHITE);
tft.print(String(filterCenter)+" Hz");
tft.updateScreenAsync();

}
////////////////////////////////////////////////////////////////////
void displayBw()
{
tft.setFont(Arial_12_Bold);

tft.useFrameBuffer(0);
tft.fillRect(247,176,65,20,ILI9341_BLACK);//erase bar

tft.setCursor(250,180);

tft.setTextColor(ILI9341_WHITE);
tft.print(String(filterBandwidth)+" Hz");
tft.updateScreenAsync();
}

///////////////////////////////////////////////////////////////////////////
void displayLevel()
{
  tft.useFrameBuffer(0);
  tft.fillRect(80, 35, 240, 5,ILI9341_BLACK);
  tft.fillRect(80, 35, int(sLevel)/2, 5,ILI9341_ORANGE);
  tft.updateScreenAsync();
}

void meterScale()
{

int y=43;
tft.setFont(Arial_10_Bold);
tft.setTextColor(ILI9341_WHITE);

tft.setCursor(77,y);
tft.print("0");  
  
tft.setCursor(103,y);
tft.print("+1");  

tft.setCursor(132,y);
tft.print("+3");  
  
tft.setCursor(159,y);
tft.print("+5");  

tft.setCursor(186,y);
tft.print("+7");  

tft.setCursor(213,y);
tft.print("+9");  

tft.setTextColor(ILI9341_RED);
tft.setCursor(240,y);
tft.print("+20");  

tft.setCursor(267,y);
tft.print("+40");  

tft.setCursor(295,y);
tft.print("+60");  
}

void spectrumScale()
{
int y=150;
tft.setFont(Arial_10_Bold);

tft.setTextColor(ILI9341_WHITE);

tft.setCursor(27,y);
tft.print("-40");  

tft.setCursor(60,y);
tft.print("-30");  

tft.setCursor(93,y);
tft.print("-20");  

tft.setCursor(120,y);
tft.print("-10");  

tft.setCursor(157,y);
tft.print("0");  

tft.setCursor(173,y);
tft.print("+10");  

tft.setCursor(205,y);
tft.print("+20");  

tft.setCursor(232,y);
tft.print("+30");  

tft.setCursor(267,y);
tft.print("+40");  

}

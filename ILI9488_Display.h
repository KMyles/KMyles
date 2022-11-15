#include <SPI.h>
#include <ILI9488_t3.h>
#include "ili9488_t3_font_Arial.h"
#include "ili9488_t3_font_ArialBold.h"

////////////////////Define pin connections for TFT and touch (TS) teensy4.0
#define TFT_RESET 3.3v    //Device RESET display
#define TFT_DC    9      //Device Connect display
#define TFT_CS    10     //Chip Select display
//        mosi    11
//        miso    12
//        sck     13
ILI9488_t3 tft=ILI9488_t3(TFT_CS, TFT_DC);
DMAMEM RAFB fb1[480 *  320];

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
 int y=53;
  
  tft.begin(50000000);
  tft.setRotation(1);
  tft.setFrameBuffer(fb1);
  tft.fillScreen(ILI9488_BLACK);
  tft.setFont(Arial_14);
  tft.setCursor(20, 35);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("S-Meter-");
  tft.updateScreenAsync();
  tft.drawLine(0,69,480,69,ILI9488_WHITE);
  tft.drawLine(0,195,480,195,ILI9488_CYAN);
////////////////////////SELECT MODE/////////////////////////////////////
  tft.fillRoundRect(10, 260,225,45, 6, ILI9488_BLUE);
  tft.setFont(Arial_14);
  tft.setCursor(30, 278);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("CW");
  tft.setCursor(100, 278);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("LSB");
  tft.setCursor(170, 278);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("USB");
///////////////////////Select Step/////////////////////////////////////////////////  
  tft.fillRoundRect(245, 260,235,45, 6, ILI9488_BLUE);
  tft.setFont(Arial_14);
  tft.setCursor(415, 278);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("1Hz");
  tft.setCursor(335, 278);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("100Hz");
  tft.setCursor(265, 278);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("1kHz");
  ///////////////////////////DISPLAY FILTER/////////////////////////////////////////
  tft.fillRect(100,220,300,2,ILI9488_WHITE);
  tft.setFont(Arial_14);
  tft.setCursor(15, 203);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("Filter FC");
  tft.fillRect(100,250,300,2,ILI9488_WHITE);
  tft.setFont(Arial_14);
  tft.setCursor(15, 232);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("Filter BW");
/////////////////////////////////////////////////////////////////////////////

tft.setFont(Arial_14);

tft.setCursor(100,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("0");  

  
tft.setCursor(135,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+1");  


tft.setCursor(175,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+3");  

  
tft.setCursor(220,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+5");  

  
tft.setCursor(265,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+7");  

tft.setCursor(305,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+9");  

tft.setCursor(345,y);
tft.setTextColor(ILI9488_RED);
tft.print("+20");  

tft.setCursor(395,y);
tft.setTextColor(ILI9488_RED);
tft.print("+40");  

tft.setCursor(443,y);
tft.setTextColor(ILI9488_RED);
tft.print("+60");  
////////////////////////////////////////////////////////////////////////
int ySpectrum=175;
tft.setFont(Arial_12);
tft.setTextColor(ILI9488_WHITE);

tft.setCursor(15,ySpectrum);
tft.print("-40");  

tft.setCursor(60,ySpectrum);
tft.print("-30");  

tft.setCursor(118,ySpectrum);
tft.print("-20");  

tft.setCursor(165,ySpectrum);
tft.print("-10");  

tft.setCursor(235,ySpectrum);
tft.print("0");  

tft.setCursor(280,ySpectrum);
tft.print("+10");  

tft.setCursor(332,ySpectrum);
tft.print("+20");  

tft.setCursor(385,ySpectrum);
tft.print("+30");  

tft.setCursor(435,ySpectrum);
tft.print("+40");    
}
////////////////////////////////////////////////////////////////////////
void displayFreq()
{ 
 
  tft.fillRect(155, 0, 180, 35,ILI9488_BLACK);
  tft.setFont(Arial_24);
  tft.setCursor(170,5);
  tft.setTextColor(ILI9488_WHITE);
  tft.print(float(Freq)/1000,3);
 
}
////////////////////////////////////////////////////////////////////
void displayMode()
{
  tft.fillRect(0, 0, 125, 35,ILI9488_BLACK);
  tft.setFont(Arial_20);
  tft.setCursor(20,5);
  tft.setTextColor(ILI9488_WHITE);
  tft.print(Mode);
}
//////////////////////////////////////////////////////////////////////////

void displayTs()
{
  tft.fillRect(350, 0, 130, 35,ILI9488_BLACK);
  tft.setFont(Arial_14);
  tft.setCursor(375,5);
  tft.setTextColor(ILI9488_WHITE);
  tft.print("TS:"+String(Step)+" Hz");
}
/////////////////////////////////////////////////////////////////////////////
void displayFc()
{
int xhF=2;

tft.useFrameBuffer(0);
tft.fillRect(100,200,388,20,ILI9488_BLACK);//erase bar
tft.fillRect(xlF,200,xhF,20,ILI9488_WHITE);
 tft.setFont(Arial_14);
tft.setCursor(405,203);
tft.setTextColor(ILI9488_WHITE);
tft.print(String(filterCenter)+" Hz");
tft.updateScreenAsync();

}
////////////////////////////////////////////////////////////////////
void displayBw()
{
int xhB=2;

tft.useFrameBuffer(0);
tft.fillRect(100,230,388,20,ILI9488_BLACK);//erase bar
tft.fillRect(xlB,230,xhB,20,ILI9488_WHITE);
tft.setCursor(405,230);
tft.setFont(Arial_14);
tft.setTextColor(ILI9488_WHITE);
tft.print(String(filterBandwidth)+" Hz");
tft.updateScreenAsync();
}
///////////////////////////////////////////////////////////////////////////
void displayLevel()
{
  tft.useFrameBuffer(0);
  tft.fillRect(100, 40, 370, 10,ILI9488_BLACK);
  tft.fillRect(100, 40, int(sLevel *1.5)-153, 10,ILI9488_ORANGE);
  tft.updateScreenAsync();
}

void spectrumScale()
{
int y=175;
tft.setFont(Arial_12);
tft.setTextColor(ILI9488_WHITE);

tft.setCursor(15,y);
tft.print("-40");  

tft.setCursor(60,y);
tft.print("-30");  

tft.setCursor(118,y);
tft.print("-20");  

tft.setCursor(165,y);
tft.print("-10");  

tft.setCursor(235,y);
tft.print("0");  

tft.setCursor(280,y);
tft.print("+10");  

tft.setCursor(332,y);
tft.print("+20");  

tft.setCursor(385,y);
tft.print("+30");  

tft.setCursor(435,y);
tft.print("+40");  
  
}

void meterScale()
{

int y=53;
tft.setFont(Arial_14);

tft.setCursor(100,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("0");  

  
tft.setCursor(135,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+1");  


tft.setCursor(175,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+3");  

  
tft.setCursor(220,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+5");  

  
tft.setCursor(265,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+7");  

tft.setCursor(305,y);
tft.setTextColor(ILI9488_WHITE);
tft.print("+9");  

tft.setCursor(345,y);
tft.setTextColor(ILI9488_RED);
tft.print("+20");  

tft.setCursor(395,y);
tft.setTextColor(ILI9488_RED);
tft.print("+40");  

tft.setCursor(443,y);
tft.setTextColor(ILI9488_RED);
tft.print("+60");  
}

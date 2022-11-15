\
#include<XPT2046_Touchscreen.h>
#define TS_PIN    6         // touch screen chip select
#define TIRQ_PIN  5       // touch IRQ   
XPT2046_Touchscreen ts(TS_PIN ,TIRQ_PIN); 

extern String Mode;
extern volatile uint32_t Step;
extern int filterCenter;
extern int filterBandwidth;
extern void SetFilter();
extern void displayMode();
extern int xlF;
extern int xlB;
void initTouch()
{
  ts.begin();
}

void selectTouch()
{
 TS_Point p = ts.getPoint();
 
      Serial.print(", x = ");
      Serial.print(p.x);
      Serial.print(", y = ");
      Serial.print(p.y);
      Serial.println();
      Serial.println("////////////////////");

      if((p.x>3500)&& p.y<800)
      {
        Mode="CW";
        filterCenter=500;
        filterBandwidth=250;
        xlF=240;
        xlB=240; 
        SetFilter();
        displayFc();
        displayBw();
        displayTs();
        displayMode();
       }

      if((p.x<3200)&&(p.x>2800)&&(p.y<800))
      {
        Mode="LSB";
        filterCenter=1650;
        filterBandwidth=2800;
        xlF=240;
        xlB=240; 
        SetFilter();
        displayFc();
        displayBw();
        displayTs();
        displayMode();
       }

      if((p.x<2700)&&(p.x>2300)&&(p.y<800))
      {
        Mode="USB";
        filterCenter=1650;
        filterBandwidth=2800;
        xlF=240;
        xlB=240; 
        SetFilter();
        displayBw();
        displayFc();
        displayTs();
        displayMode();
       }

      /////////////////////////////////////////////tuning Step///////
      if((p.x<2000)&&(p.x>1600)&&(p.y<800))
      {
        Step=1000;
        displayTs();  
      }
      if((p.x<1400)&&(p.x>800)&&(p.y<800))
      {
        Step=100;
        displayTs();
      }
      if((p.x<700)&&(p.y<800))
      {
        Step=1;
        displayTs();
      }
    
}

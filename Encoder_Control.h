#include <Encoder.h>
Encoder tuning(4,3);
Encoder filter(14,15);
Encoder bandwidth(2,1);

extern void SetFrequency();

extern volatile uint32_t Freq ; // frequency
extern volatile uint32_t Step ; // sets the tuning increment

extern long oldTuning;
extern long newTuning;
///////////////////////////////////////////////////////////
extern long oldFilter;
extern long newFilter;
extern int xlF;
extern int filterCenter;
extern int fcUpper;
extern int fcLower;
////////////////////////////////////////////////////////////
extern long oldBandwidth;
extern long newBandwidth;
extern int xlB;
extern int filterBandwidth;
extern int BwUpper;
extern int BwLower;
/////////////////////////////////////////////////////////////
extern void SetFrequency();
extern void SetFilter();
/////////////////////////////////////////////////////////////
void Encoder_Controller()
{
   newTuning=tuning.read()/4 ;
     if(newTuning!=oldTuning)
     {
      if(newTuning>oldTuning)
      {
        Freq=Freq+Step;
       
      }
     if(newTuning<oldTuning)
      {
        Freq=Freq-Step;
             
      }
      SetFrequency();
      oldTuning=newTuning;
      }
//////////////////////////////////////////////////////////////////////////
     newFilter=filter.read()/4;
     if(newFilter!=oldFilter)
     {
      if(newFilter>oldFilter)
      {
        if(filterCenter<2500)
        {
          xlF=xlF+1;
          filterCenter=filterCenter+10;
          SetFilter();
        }
        else
        {
         filterCenter=2500;
        }
      }
      if(newFilter<oldFilter)
      {
       if(filterCenter>250)
       { 
         xlF=xlF-1;
         filterCenter=filterCenter-10;
          SetFilter();
       }
       else
       {
        filterCenter=250;
       }
      }
      oldFilter=newFilter;
      displayFc();
     }
 
///////////////////////////////////////////////////////////////////////////
    newBandwidth=bandwidth.read()/4;
     if(newBandwidth!=oldBandwidth)
     {
      if(newBandwidth>oldBandwidth)
      {
        if(filterBandwidth<5000)
        {
            xlB=xlB+1;
            filterBandwidth=filterBandwidth+25;
            SetFilter();
        }
        else
        {
           filterBandwidth=5000;
        }
      }
      if(newBandwidth<oldBandwidth)
      {
        if(filterBandwidth>100)
        {
          xlB=xlB-1;
          filterBandwidth=filterBandwidth-25;
          SetFilter();
        }
        else
        {
          filterBandwidth=100;
        }
      }
      oldBandwidth=newBandwidth;
      displayBw();
     }
 }

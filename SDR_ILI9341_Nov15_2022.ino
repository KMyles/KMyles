/* Service Release 11/15/2022

 Due to changes in the DSP library .. There was some DSP Library contention from the 
 ILI9341 and ILI9488 builds. Which caused compile issues.
 at the time of the build release in Jan 2022 the Convolutional filter was not integrated into the OpenAudio Library
 the filter has since been added to the Library and I needed to clean items up to avoid build frustration for other builders
 the compiled .hex files will load fine on the olde Jan 13/2022 build 

 First the usual disclaimer ..You are building at your own risk!!
 I will hold no liability if you damage a component involved with this build
 if you are good with this ..enjoy!
   
 This code is for non-commercial use and not for resale!!!
   
   it was build as an educational platform to learn and develope SDR code 
   is very open ended, coding contributions greatly accepted
  
   All code is in the public domain .
 
 Big Thanks to Bob  W7PUA for a super DSP library 
 Big Thanks to Mike K7MDL for the super spectrum waterfall display code for the RA8875 
 Big Thanks to Giuseppe Callipo IK8YFW for the Convolutional filter code!! 
  
  THIS BUILD has a convolutional filter 
    
  Bandwidth filtering is accomplished wiht variable filter and 2 mechanical encoders
  
**********************************************************************************************************
   This Build was compiled on Arduino 2.01 with the teensy extensions and the teensy loader 1.55

   It will also compile on arduino ide 1.18.16 with teensy Loader 1.55

  Required Libraries ...

             Etherkit SI5351  NT7s Library available in your arduino ide library tool..
                      ILI9341  https://github.com/KurtE/ILI9341_t3n
             OpenAudio         https://github.com/IDC-Dragon/OpenAudio_ArduinoLibrary.git

             *****************************************************************************
             Note the location of the Openaudio Library .. it is a fork of ChipOdette Library !!
             You cannot compile on the Chip odette Library due to the new version we are running in the link above!

            if You are compiling a new build , it would be best to delete the old openaudio library
            and download the current one ffrom the link above

            I would like to thank  everyone who has come onboard , offered advice, troubleshooting and inspiration for the build 
                73 from OM Keith
                VE3IFT (re-issue pending)



             ********************************************************************************************
Code is located at 

                           HTTPS://GITHUB.COM/KMYLES/KMYLES.GIT

 Support can be found in 2 locations 
 * 
 * FACEBOOK group Keiths_SDR ( the fun and not so formal group)
 * 
 * KeithSdr@groups.io ( the more formal) leave requsets for support in the messages section
 *  
 * Note the following pinouts have changed 
 * 
 * for ILI9341/ILI9488 TFT display portion
 * 
 * teensy pin   Display
 * 13 sck       SCK
 * 12 miso      MISO
 * 11 mosi      MOSI
 * 10 CS        CS
 *  9 DC        DC
 *  3.3v        Reset  new pinout
 *  
 *  for touch portion
 *  teensy pin  Display
 *  
 *  13 SCK      t_CLK
 *  6           T_CS   new pinout
 *  5           T_IRQ  new pinout
 *  11 MOSI     T_DIN  
 *  12 MISO     R_D0
 * 
 * Tuning encoder 
 * teensy pins 4,3     new pinout
 * 
 * Center Frequenncy encoder
 * Teensy pins 14,15   sets the center frequency of the filter  new pinout
 * 
 * Bandwidth encoder 2,1 sets the filter bandwidth  new pinout

 I 


*/

#include "VFO.h"
#include "DSP.h"
#include "Encoder_Control.h"
#include "Touch_Controller.h"
#include <Metro.h>

volatile uint32_t Freq =7250000; // default power up frequency//////////
volatile uint32_t Step =1000; // default power up frequency//////////

long oldTuning=-999;
long newTuning;
///////////////////////////////////////////////////////////
long oldFilter=-999;
long newFilter;
int xlF=240;
int filterCenter=1650;
int fcUpper=2800;
int fcLower=250;
////////////////////////////////////////////////////////////
long oldBandwidth=-999;
long newBandwidth;
int xlB=240;
int filterBandwidth=2800;
int BwUpper=4000;
int BwLower=250;
/////////////////////////////////////////////////////////////
String Mode="";
float sLevel;
long I;
long Q;
Metro touch=Metro(300);
Metro meter=Metro(250);



void setup() 
{
initTouch();
initTemplate();
initVfo();
initDsp();  

displayFreq();
displayMode();
displayTs();
displayFc();
displayBw();
displayLevel();
meterScale();
spectrumScale();
SetFrequency();
selectModeUSB();  

}

void loop() 
{
  Encoder_Controller();


  if(touch.check()==1)
 {
  if(ts.touched())  
   {  
    selectTouch();
   }
 }  
 
if(meter.check()==1)
{
 getRMS();
 displayLevel();
}

Spectrum_ILI9341();
}

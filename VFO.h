

#include <Wire.h>
#include <si5351.h> 
#include <Encoder.h>

Encoder Tune(31,30);  //Sets the Encoder pins, if the encoder turns in the opposit direction switch pins (30,31)
Si5351 si5351;        // USe the etherkit si5351 library in your Library manager in Arduino IDE


long oldF  = -999; // just a strating point 
long newF;    

uint32_t F_Upper=30000000;  // Sets upper tuning limit 30 MHz
uint32_t F_Lower=1000000;   // Sets lower tuning Limit 1 MHz

volatile uint32_t Frequency=7225000; //Sets a Default Frequency
volatile uint32_t Step=1000;         // Sets the initial step  

int n=0;

//////////////////////////Initialize VFO/DDS//////////////////////////////////////////////////////
void initVfo()
{
 delay(50);
 si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0); // Sets XTAL Load Capacitance 6/8/10 pf
 si5351.set_correction(0, SI5351_PLL_INPUT_XO);// 0 is the calibration factor for my si5351
 si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
 si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA); // Sets the output level of the SI5351
 si5351.set_freq(Frequency *400ULL , SI5351_CLK0);  // note the *400ULL multiplies the Frequency by 4 for tayloe detectors Set to *100ULL for direct Frequency output
}

void initStep()
{
  pinMode(32, INPUT_PULLUP);  // Use pin 32 for the switch on the rotary encoder

}

void setStep()
{   
     if(digitalRead(32)==LOW)  //Switch pushed ??
    {  
      delay(300);  //debounce

      if(n==0)  
      {
        Step=1000;  //select step  
      }
    
      if(n==1)
      {
        Step=100;  //select step
      }

      if(n==2)
      {
        Step=10;  //select step
      }

      if(n==3)
      {
        Step=1;  //select step
      }

      if(n==4)
      {
        n=0;   // no more steps
      }
      else
      {
        n=n+1; // still steps left
      }

    
       Serial.println("STEP: "+ String(Step));  //show me the step in serial monitor
    }
    
}

void SetFrequency()
{ 
   si5351.set_freq((Frequency) *400ULL, SI5351_CLK0); // generating 4 x frequency ... set 400ULL to 100ULL for 1x frequency
   Serial.println(Frequency);  //show me the frequency 
}

/*********************************************************tuning**********************************************/

void changeFrequency()
{
   newF = Tune.read()/4;  //get the encoder value

   if (newF != oldF) // not equal to current encoder
  {
    ///////////////////// if its greater count up
    if(newF>oldF)
      {
          Frequency=Frequency+Step;
          if (Frequency>F_Upper)
          {
            Frequency=F_Upper;
          }
     
      }
      ///////////////////////if its lower count down////////////////
      if(newF<oldF)
      {
        Frequency=Frequency-Step;
           if(Frequency<F_Lower)
           {
           Frequency=F_Lower;
           }
        
      }
         SetFrequency(); //set the frequency
         oldF = newF; //current frequency is now old frequency
}

}
     



#include "VFO.h"  //makes sure to add in the vfo.h file

volatile uint32_t Freq =7035000; // default power up frequency//////////

void setup() {
  // put your setup code here, to run once:
  delay(50);
initVfo();
delay(100);
SetFrequency();

}

void loop() {
  // put your main code here, to run repeatedly:

}

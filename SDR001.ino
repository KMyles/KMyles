#include <Wire.h> 
#include "display.h"

volatile uint32_t Freq =7035001; // default power up frequency//////////
volatile uint32_t Step =100; // default power up step//////////



void setup() {

  displayInit();

   displayFreq();
}

void loop() {
  
 
}

#include <Wire.h> //we nneed the wire.h library for I2C communication
#include "display.h" //WWe want to include our display code 

volatile uint32_t Freq =7035001; // default power up frequency//////////
volatile uint32_t Step =100; // default power up step//////////



void setup() {

  displayInit();  //lets set up or initialze our display 

   displayFreq(); //lets display a freq 
}

void loop() {
  
 
}

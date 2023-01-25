/*
* SI5351 VFO   JAN 25/2023
* THIS IS FOR THE TEENSY 4.1
* USE AT YOUR OWN RISK!!
*
* Connections
* TEENSY             SI5351
* VCC (5V)             VCC  (CAUTION VErify The SI5351 is for 5v. Some are 3.3v)
* GND                  GND
* PIN 19               SCL
* Pin 18               SDA

* TEENSY               k040 Rotary Encoder Switch to set Frequency Step 1000/100/10/1 Hz
* VCC (3.0v)           k040 +3.3v                  
* GND                  GND
* PIN 30               CLK
* PIN 31               DT
* PIN 32               SW  

* Confirm all your wiring is correcct
* Compile and load into the teensy 4.1
* Launch your Serial Monitor ()
* Frequency and STEP will be displayed in the monitor
* Encoder will change frequency Up/Down0
* pushing the momentary contact on the switch will change Tuning Step
*
* SEE NOTES IN VFO.H
*/

#include "VFO.h"  

void setup() {

Serial.begin(9600);
delay(250);

initVfo();
initStep();
SetFrequency();

}

void loop() {
 
 changeFrequency();
 setStep();

}

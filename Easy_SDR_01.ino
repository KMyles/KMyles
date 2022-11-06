#include <Wire.h>
#include "Display_4002.h"
#include "Controls_I2C.h"
#include "vfo.h"

volatile uint32_t freq=7255000;

int step=10;

void setup() {

// Serial.begin(115000);
 Wire.setClock(400000); 
 delay(50);
 InitDisplay();
 delay(50);
 InitControl();
 delay(50);
 initVfo();

}

void loop() {

GetControl();
  
}



/* Jabuary 16 2023 ... SDR Generic FrameworkBeta Test
 *  
 * * There is no filtering/bandwidth selection on this release
 * 
 * Built on ......
 * Arduino 2.0.03
 * teensyduino 1.57
 * 
 * Required Libraries ...
 * 
 *      ili9488_T3  https://github.com/mjs513/ILI9488_t3
 *      Openaudio https://github.com/chipaudette/OpenAudio_ArduinoLibrary
 *        
 *       si5351  NT7s Library available in your arduino ide library tool..
 * 
 * 
 * 
 * Note the following pinouts have changed 
 * 
 * for display portion
 * teensy pin   Display
 * 13 sck       SCK
 * 12 miso      MISO
 * 11 mosi      MOSI
 * 10 CS        CS
 *  9 DC        DC
 * 14 Reset     Reset // reset has been added
 *  
 *  for touch portion
 *  teensy pin  Display
 *  13 SCK      t_CLK
 *  5           T_CS
 *  4           T_IRQ
 *  11 MOSI     T_DIN  
 *  12 MISO     R_D0
 * 
 * Rotary encoder for the tuner is now on teensy pins 14,15
 * 
 * Double check your connections ...
 */

 //////////////////////////////////////////////////////////////////////////////////

#include "ILI9488_Display.h"  
#include "VFO.h"  
#include "DSP.h"

void setup() {

initVfo();
initDisplay();
initDsp();

}

void loop() {

changeFrequency();



}



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
 *   EXTERNAL A/D and D/A converters
 *   COmmon Ones 
 *   PCM1802
 *   DAC5402
 *   
 *   Both Devices need Teensy pins set up hardware wise 
 *
 *   Teensy 4.0/4.1
 *   MCLK1 ----    Pin 23    
 *   BCLK1 -----   Pin 23 
 *   IN1 (Data)    Pin 7
 *   OUT1C (Data)  Pin 8
 *
 *   Note Some devices do not use MCLK1 They derive clock from B Clock  
 *  
 *   https://www.ebay.com/itm/125254850441  I used this A/D
 *   https://www.ebay.com/itm/311704263039  I used this D/A 
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

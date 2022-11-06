#include <i2cEncoderMiniLib.h>

extern volatile uint32_t freq;
extern int step;
extern void DisplayFreq();
extern void SetFrequency();
const int IntPin = 20; 
i2cEncoderMiniLib Encoder1(0x42); 

void encoder1_increment(i2cEncoderMiniLib* obj) {
  freq=freq+step;
  SetFrequency();
 // Serial.println(freq);
}

 void encoder1_decrement(i2cEncoderMiniLib* obj) {
  freq=freq-step;
  DisplayFreq();
  SetFrequency();
 // Serial.println(freq);
  }

 void InitControl()

{
  pinMode(IntPin, INPUT);
 

  Encoder1.reset();
 // Encoder1.begin(i2cEncoderMiniLib::WRAP_DISABLE
 //               | i2cEncoderMiniLib::DIRE_LEFT | i2cEncoderMiniLib::IPUP_ENABLE
 //               | i2cEncoderMiniLib::RMOD_X1 );
 Encoder1.begin(i2cEncoderMiniLib::DIRE_LEFT | i2cEncoderMiniLib::RMOD_X1);
  Encoder1.onIncrement = encoder1_increment;
  Encoder1.onDecrement = encoder1_decrement;
  
  Encoder1.autoconfigInterrupt();
 
}
  void GetControl()
  {
   if (digitalRead(IntPin) == LOW)
    {
     Encoder1.updateStatus();
    }

  }

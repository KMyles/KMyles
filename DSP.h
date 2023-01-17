#include "Audio.h"       // Teensy I16 Audio Library
#include "OpenAudio_ArduinoLibrary.h" // F32 library
#include "AudioStream_F32.h"
//

float32_t dbA[2000];
float32_t workSpace[4128];
float32_t equalizeCoeffs[4000];


const float sample_rate_Hz = 192000.0f ;  // 24000, 44117, or other frequencies listed above
const int   audio_block_samples = 128;

AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

AudioInputI2S_F32           Input(audio_settings);

AudioOutputI2S_F32          Output(audio_settings);

AudioConnection_F32     patchCordL(Input,0, Output,0);
AudioConnection_F32     patchCordR(Input,1, Output,1);

void initDsp()
{

 AudioMemory(16); // 16 bit audio memory allocation
 AudioMemory_F32(20, audio_settings);

}

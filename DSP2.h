#include "OpenAudio_ArduinoLibrary.h"
#include "AudioStream_F32.h"
#include "Hilbert.h"
#include <Audio.h>
#include <Wire.h>
#include "AudioFilterFIRGeneral_F32.h"

const float sample_rate_Hz = 48000.0f ;  // 24000, 44117, or other frequencies listed above
const int   audio_block_samples = 128;

AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

// GUItool: begin automatically generated code
AudioInputI2S_F32        audioInI2S1;    //xy=175,228
AudioFilterFIRGeneral_F32 filterFIRgeneral2; //xy=340,273
AudioFilterFIRGeneral_F32 filterFIRgeneral1; //xy=346,159
AudioMixer4_F32          mixer4_1;       //xy=564,217
AudioOutputI2S_F32       audioOutI2S1;   //xy=838,212
AudioConnection_F32          patchCord1(audioInI2S1, 0, filterFIRgeneral1, 0);
AudioConnection_F32          patchCord2(audioInI2S1, 1, filterFIRgeneral2, 0);
AudioConnection_F32          patchCord3(filterFIRgeneral2, 0, mixer4_1, 1);
AudioConnection_F32          patchCord4(filterFIRgeneral1, 0, mixer4_1, 0);
AudioConnection_F32          patchCord5(mixer4_1, 0, audioOutI2S1, 0);
AudioConnection_F32          patchCord6(mixer4_1, 0, audioOutI2S1, 1);
// GUItool: end automatically generated code


void initDsp()
{

float32_t workspace[4128];

AudioMemory(20); // 16 bit audio memory allocation
AudioMemory_F32(50, audio_settings);

filterFIRgeneral1.LoadCoeffs(251, Hilbert_Plus45_3000H,workspace);
filterFIRgeneral2.LoadCoeffs(251, Hilbert_Minus45_3000H,workspace);
mixer4_1.gain(0,1.0);
mixer4_1.gain(1,-1.0);

}
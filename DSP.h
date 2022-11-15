#include <Audio.h>
#include "OpenAudio_ArduinoLibrary.h" // F32 library
#include "Hilbert.h"
#include "ILI9341_display.h"

const float sample_rate_Hz = 96000.0f;
const int   audio_block_samples = 128;
extern int filterCenter;
extern int filterBandwidth;
extern float sLevel;
extern String Mode;
extern void displayMode();


AudioSettings_F32 audio_settings(sample_rate_Hz, audio_block_samples);

AudioFilterFIR_F32      RX_Hilbert_Plus_45(audio_settings);
AudioFilterFIR_F32      RX_Hilbert_Minus_45(audio_settings);
AudioMixer4_F32         RX_Summer(audio_settings);
AudioAnalyzeRMS_F32     RMS;
AudioAnalyzeFFT256_IQ_F32 FFT; 
AudioFilterConvolution_F32 FilterConv(audio_settings);

AudioInputI2S_F32       Input(audio_settings);
AudioOutputI2S_F32      Output(audio_settings);

AudioControlSGTL5000    codec1;  

AudioConnection_F32     patchCord0L(Input,0, FFT,1);
AudioConnection_F32     patchCord0R(Input,1, FFT,0);

AudioConnection_F32     patchCord1L(Input,0,RX_Hilbert_Plus_45,0);
AudioConnection_F32     patchCord1R(Input,1,RX_Hilbert_Minus_45,0);

AudioConnection_F32     patchCord2L(RX_Hilbert_Plus_45,0,RX_Summer,0);
AudioConnection_F32     patchCord2R(RX_Hilbert_Minus_45,0,RX_Summer,1);

AudioConnection_F32     patchCord3l(RX_Summer,0,FilterConv,0);
AudioConnection_F32     patchCord3M(RX_Summer,0,RMS,0);

AudioConnection_F32     patchCord3L(FilterConv,0,Output,0);
AudioConnection_F32     patchCord3R(FilterConv,0,Output,1);


void initDsp()
{
  AudioMemory(16);
  AudioMemory_F32(20, audio_settings);
  codec1.enable();  // MUST be before inputSelect()
  codec1.inputSelect(AUDIO_INPUT_LINEIN);
  codec1.lineInLevel(13);
  codec1.lineOutLevel(5);  
  codec1.volume(0.5);
  codec1.adcHighPassFilterDisable();
 
 RX_Hilbert_Plus_45.begin(Hilbert_Plus45_3200H,151);   //Left Channel
 RX_Hilbert_Minus_45.begin(Hilbert_Minus45_3200H,151);  //Right Channel
 
}
void selectModeCW()
{
 RX_Summer.gain(0,0.5);
 RX_Summer.gain(1,0.5);
//SetFilter();
 Mode="CW";
displayMode();
}

void selectModeLSB()
{
 RX_Summer.gain(0,1.0);
 RX_Summer.gain(1,-1.0);
 FilterConv.initFilter((float32_t)1500, 90, 2, 3000);//
//SetFilter();
 Mode="LSB";
 displayMode();
}

void selectModeUSB()
{
 RX_Summer.gain(0,0.5);
 RX_Summer.gain(1,0.5);
// SetFilter();
 Mode="USB";
 displayMode();
}

void SetFilter()
{
    FilterConv.initFilter((float32_t)filterCenter, 90, 2, filterBandwidth);
}

void getRMS()
{
 if(RMS.available())
  {
   sLevel=RMS.read();
   sLevel = 20*log(sLevel/.0000001);
 //  displayLevel();
  }
}

void Spectrum_ILI9341()
{
  float* pPwr;
  int bar;
  FFT.setOutputType(FFT_RMS);
 // Select the wndow function
  //FFT256iq1.windowFunction(AudioWindowNone);
  //FFT256iq1.windowFunction(AudioWindowHanning256);
  //FFT256iq1.windowFunction(AudioWindowKaiser256, 55.0f);
  FFT.windowFunction(AudioWindowBlackmanHarris256);
  FFT.setXAxis(0X03);
  FFT.setNAverage(15); 
  if(FFT.available())
 {
      pPwr = FFT.getData();
     for(int i=1                                                                                                            ; i<256; i++)
     {
      bar= int(*(pPwr + i)*100);
     // bar=bar/6;
      if (bar >60) bar=60;

       tft.drawFastVLine((i*1)+32, 145-bar,bar,ILI9341_YELLOW);
       tft.drawFastVLine((i*1)+32, 80,64-bar,ILI9341_BLACK);   
     }
    
 }
}
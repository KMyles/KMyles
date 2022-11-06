#include <si5351.h> 
Si5351 si5351;

extern volatile uint32_t freq;
extern void DisplayFreq();
//////////////////////////Initialize VFO/DDS//////////////////////////////////////////////////////
void initVfo()
{
 delay(50);
 si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
 si5351.set_correction(33000, SI5351_PLL_INPUT_XO);//33000 is the calibration factor for my si5351
 si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
 si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_6MA);
 si5351.set_freq(freq *400ULL , SI5351_CLK0); 
}

void SetFrequency()
{ 
  si5351.set_freq((freq) *400ULL, SI5351_CLK0); // generating 4 x frequency ... set 400ULL to 100ULL for 1x frequency
  DisplayFreq();
}

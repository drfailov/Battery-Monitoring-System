#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
bool adsReady = false;
//ads Current Pins is 0 , 1
int readingFor1A = 128;  //1A = 128


void CurrentMeasureInit(){
  adsReady = ads.begin();
  if(!adsReady) {
    Serial.println("Failed to initialize ADS.");
    return;
  }
  ads.setGain(GAIN_SIXTEEN);
}

int16_t getCurrentRaw(){
  if(!adsReady)
    return 0;
  long sum = 0;
  for(byte i=0; i<3; i++)
    sum += ads.readADC_Differential_0_1();
  return sum / 3;
}

long getCurrent_mA(int16_t raw){
  return raw * 1000l / readingFor1A;
}
long getCurrent_mA(){
  return getCurrentRaw() * 1000l / readingFor1A;
}

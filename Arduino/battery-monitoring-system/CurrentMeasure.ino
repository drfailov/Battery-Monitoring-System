#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
bool adsReady = false;
const byte ADS1115PowerPin = A0;
//ads Current Pins is 0 , 1
int readingFor1A = 128;  //1A = 128
long lastReadCurrent_mA = 0;

long powerCounterLastReadTime = 0;
float WhSinceFullCharge = 0;
float WhSinceReset = 0;


void CurrentMeasureInit(){
  pinMode(ADS1115PowerPin, OUTPUT);
  digitalWrite(ADS1115PowerPin, HIGH);
  delay(10);
  adsReady = ads.begin();
  if(!adsReady) {
    Serial.println("Failed to initialize ADS.");
    return;
  }
  ads.setGain(GAIN_SIXTEEN);

  WhSinceReset = eepromReadWattmeterSinceReset();
  WhSinceFullCharge = eepromReadWattmeterSinceFull();
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
  long current_mA = raw * 1000l / readingFor1A;
  float voltage = getCell3Voltage();
  float voltagePerCell = voltage / 3.0;    
  float currentA = (float)current_mA / 1000.0f;
  float power = voltage*currentA;
  long dT_ms = millis() - powerCounterLastReadTime;   
  //reset counter if full charge
  if(lastReadCurrent_mA > 0 && current_mA <= 0 && voltagePerCell > 4.15f) {
    resetPowerCounterSinceFullCharge();
    message(F("RESET Wh_S_FULL"));
  }

  //update power counter  
  if(powerCounterLastReadTime != 0){
    float dT_s = ((float)dT_ms) / 1000.0;
    float dT_m = ((float)dT_s) / 60.0;
    float dT_h = ((float)dT_m) / 60.0;
    
    WhSinceFullCharge += (power*dT_h);
    WhSinceReset += (power*dT_h);

    if(abs(eepromReadWattmeterSinceReset()-WhSinceReset) > 1.0f){
      eepromSaveWattmeterSinceReset(WhSinceReset);
      message(F("SAVED Wh_S_RESET"));
    }
    if(abs(eepromReadWattmeterSinceFull()-WhSinceFullCharge) > 1.0f){
      eepromSaveWattmeterSinceFull(WhSinceFullCharge);
      message(F("SAVED Wh_S_FULL"));
    }
    //mAh += (current*dT_h);
  }
  lastReadCurrent_mA = current_mA;
  powerCounterLastReadTime = millis();
  return current_mA;
}

float getWhSinseReset(){
  return WhSinceReset;
}

float getWhSinseFullCharge(){
  return WhSinceFullCharge;
}

void resetPowerCounterSinceFullCharge(){
  WhSinceFullCharge = 0;
}

void resetPowerCounter(){
  WhSinceReset = 0;
}

long getCurrent_mA(){
  getCurrent_mA(getCurrentRaw());
}

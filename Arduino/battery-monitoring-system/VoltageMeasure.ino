#include <INA3221.h>
const byte INA3221PowerPin = A1;
INA3221 ina_0(INA3221_ADDR40_GND);


long readingIntervalMs = 100;
float getCell1VoltageLastReadingValue = -1;
unsigned long getCell1VoltageLastReadingTime = 0;
float getCell2VoltageLastReadingValue = -1;
unsigned long getCell2VoltageLastReadingTime = 0;
float getCell3VoltageLastReadingValue = -1;
unsigned long getCell3VoltageLastReadingTime = 0;

void voltageMeasureInit(){
  pinMode(INA3221PowerPin, OUTPUT);
  digitalWrite(INA3221PowerPin, HIGH);
  delay(10);
  
  ina_0.begin(&Wire);
  ina_0.reset();
  ina_0.setShuntRes(100, 100, 100);
}

int16_t getSystemCurrent_mA(){
  return ina_0.getCurrent(INA3221_CH1) * 1000;//(long)(ina_0.getCurrent(INA3221_CH1) * 1000.0f);
}

float getCell1Voltage(){
  if(getCell1VoltageLastReadingValue==-1 || millis()-getCell1VoltageLastReadingTime>readingIntervalMs){
    getCell1VoltageLastReadingValue = ina_0.getVoltage(INA3221_CH3);
    getCell1VoltageLastReadingTime = millis();
  }
  return getCell1VoltageLastReadingValue;
}

float getCell2Voltage(){
  if(getCell2VoltageLastReadingValue==-1 || millis()-getCell2VoltageLastReadingTime>readingIntervalMs){
    getCell2VoltageLastReadingValue = ina_0.getVoltage(INA3221_CH2);
    getCell2VoltageLastReadingTime = millis();
  }
  return getCell2VoltageLastReadingValue;
}

float getCell3Voltage(){
  if(getCell3VoltageLastReadingValue==-1 || millis()-getCell3VoltageLastReadingTime>readingIntervalMs){
    getCell3VoltageLastReadingValue = ina_0.getVoltage(INA3221_CH1);
    getCell3VoltageLastReadingTime = millis();
  }
  return getCell3VoltageLastReadingValue;
}

float getAvgCellVoltage(){
  return getCell3Voltage() / 3.0f;
}

float getMinCellVoltage(){
  float c1 = getCell1Voltage();
  float c2 = getCell2Voltage()-c1;
  float c3 = getCell3Voltage()-c2-c1;
  float min = c1;
  if(c2 < min)
    min = c2;
  if(c3 < min)
    min = c3;
  Serial.print("minV="); Serial.println(min);
  return min;
}
float getMaxCellVoltage(){
  float c1 = getCell1Voltage();
  float c2 = getCell2Voltage()-c1;
  float c3 = getCell3Voltage()-c2-c1;
  float max = c1;
  if(c2 > max)
    max = c2;
  if(c3 > max)
    max = c3;
  Serial.print("maxV="); Serial.println(max);
  return max;
}

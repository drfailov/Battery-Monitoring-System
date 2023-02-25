#include <INA3221.h>

const byte INA3221PowerPin = A1;

INA3221 ina_0(INA3221_ADDR40_GND);

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
  float volt = ina_0.getVoltage(INA3221_CH3);
  return volt;
}

float getCell2Voltage(){
  return ina_0.getVoltage(INA3221_CH2);
}

float getCell3Voltage(){
  return ina_0.getVoltage(INA3221_CH1);
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

#include <INA3221.h>

INA3221 ina_0(INA3221_ADDR40_GND);

void voltageMeasureInit(){
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

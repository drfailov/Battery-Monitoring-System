#include <EEPROM.h>
const int eepromAddressWattmeterSinceReset = 10;
const int eepromAddressWattmeterSinceFull = 20;

float eepromReadWattmeterSinceReset(){
  float result;
  EEPROM.get(eepromAddressWattmeterSinceReset, result);
  if(isnan(result))
    result = 0;
  return result;
}
void eepromSaveWattmeterSinceReset(float data){
  EEPROM.put(eepromAddressWattmeterSinceReset, data);
}



float eepromReadWattmeterSinceFull(){
  float result;
  EEPROM.get(eepromAddressWattmeterSinceFull, result);
  if(isnan(result))
    result = 0;
  return result;
}
void eepromSaveWattmeterSinceFull(float data){
  EEPROM.put(eepromAddressWattmeterSinceFull, data);
}

const byte displayBacklightPin = 9;
const byte displayPowerPin = 8;
const byte buzzerPin = 7;


char buffer[20];
char messageText[20];
long messageSetTime = 0;
void message(__FlashStringHelper* m){
  Serial.print(millis()); Serial.print(": "); Serial.println(m);
  strcpy_P(messageText, (char*)m);
  messageSetTime = millis();
}

const byte STATE_STANDBY = 0;
const byte STATE_ACTIVE = 3;
const byte STATE_DEBUG = 5;
byte state = STATE_STANDBY;
long stateSetTime = 0;
/*
 * Standby 
 *    No output voltage
 * Storage Discharging 
 *    Turns on automatically when battery is leave unused for 7 days with charge level above 3.90v per cell.  
 *    No output voltage, built-in relay discharges battery until 50% of charge. Then state Standby.
 * Storage Alert
 *    If batteryLong-term storage with less then 3.60v per cell for over 7 days.
 *    No output voltage. Beeper is beeping every 10 minutes, alert on screen. Backlight is flashing every 10 minutes.
 * Turned On
 *    Turn on by pressing button for 5 seconds. Output relay is activated, system is powered on.
 *    Automatically goes to standby mode of power consumption less then 5W after 24h.
 * Deep Sleep
 *    Display is off, arduino is sleeping.
*/




void setup() {
  Serial.begin(115200);
  relaySetup();
  Display_Setup();
  backlightInit();
  CurrentMeasureInit();
  voltageMeasureInit();

  
  if(isButtonPressedNow()){ //debug startup
    state = STATE_DEBUG;
    stateSetTime = millis();
    buzzerLongBeep();
  }
  else{ //normal startup
    buzzerInit();
  }
  message(F("READY"));
}

void loop() {
  if(state == STATE_DEBUG){
    Display_Loop_Debug();
  }
  else{
    Display_Loop();
    buttonLoop();
    backlightLoop();
    buzzerLoop();
  }

  if(state == STATE_STANDBY){
    if(isButtonPressedNow()){    //change mode from standby to active by button
      unsigned long st = millis();
      while(isButtonPressedNow() && millis() - st < 3000) Display_Loop();
      if(isButtonPressedNow()){
        activeMode();
        return;
      }
    }

    if(millis()-stateSetTime > 1000L*60L*60L*24L*3L /*3 days*/){ //go to storage while standby
    //if(millis()-stateSetTime > 1000L*60L*10L /*10 min*/){ //go to storage while standby
    //if(millis()-stateSetTime > 1000L*30L/*30 sec*/){ //go to storage while standby  
      if(getAvgCellVoltage() > 3.85f){
        enableStorageDischarge();
      }
      if(getAvgCellVoltage() < 3.80f){
        disableStorageDischarge();
      }
    }
  }
  else if(state == STATE_ACTIVE){    
    if(isButtonPressedNow()){   //change mode from active to standby by button
      unsigned long st = millis();
      while(isButtonPressedNow() && millis() - st < 3000) Display_Loop();
      if(isButtonPressedNow()){
        standbyMode();
        return;
      }
    }
    if(getMinCellVoltage() < 3.25 && getCurrent_mA() < 0){  //Low voltage shutdown
        standbyMode();
        message(F("LOW VOLT OFF"));
        return;
    }
    if(getMaxCellVoltage() > 4.25 && getCurrent_mA() > 0){  //High voltage shutdown
        standbyMode();
        message(F("HIGH VOLT OFF"));
        return;
    }
    if(getBatteryTemp() > 60){  //High temp shutdown
        standbyMode();
        message(F("HIGH BAT TEMP OFF"));
        return;
    }
    if(getShuntTemp() > 80){  //High temp shutdown
        standbyMode();
        message(F("HIGH SHUNT TEMP OFF"));
        return;
    }
    if(abs(getCurrent_mA()) > 2000){  //activate high power relay
       enableHighPowerOutput();
    }
    if(abs(getCurrent_mA()) < 1500){  //deactivate high power relay
       disableHighPowerOutput();
    }
  }
  
}





// useful functions
void standbyMode(){
  state = STATE_STANDBY;
  disableLowPowerOutput();
  disableHighPowerOutput();
  disableStorageDischarge();
  stateSetTime = millis();
  message(F("OUTPUT DISABLE"));
  buzzerPlayOff();
}

void activeMode(){
  state = STATE_ACTIVE;
  stateSetTime = millis();
  enableLowPowerOutput();
  disableStorageDischarge();
  message(F("OUTPUT ENABLE"));
  buzzerPlayOn();
}


void enableLowPowerOutput(){
  if(!isEnabledLowPowerOutput()){
    relay1On();
  }
}
void disableLowPowerOutput(){
  if(isEnabledLowPowerOutput())
    relay1Off();
}
bool isEnabledLowPowerOutput(){
  return getRelay1State();
}


void enableHighPowerOutput(){
  if(!isEnabledHighPowerOutput()){
    relay2On();
    message(F("HI_PWR RELAY ON"));
  }
}
void disableHighPowerOutput(){
  if(isEnabledHighPowerOutput()){
    relay2Off();
    message(F("HI_PWR RELAY OFF"));
  }
}
bool isEnabledHighPowerOutput(){
  return getRelay2State();
}


void enableStorageDischarge(){
  if(!isEnabledStorageDischarge()){
    relay3On();
    message(F("STO ENABLED"));
  }
}
void disableStorageDischarge(){
  if(isEnabledStorageDischarge()){
    relay3Off();
    message(F("STO DISABLED"));
  }
}
bool isEnabledStorageDischarge(){
  return getRelay3State();
}



int analogReadAverage(byte pin){
  //do analogread twice with 10ms delay
  //https://forum.arduino.cc/t/adc-voltmeter-linearity-problems-solved/299805/2
  analogRead(pin);
  delay(10);
  int average = 0;
  for (int i=0; i < 10; i++) 
    average = average + analogRead(pin);
  return average/10;
}


void ttostr(long time, char* buffer){
  /*receive time in ms and print readable time to buffer*/
  long totalS = time / 1000;
  long sph = 60L*60L;
  long hours = totalS / sph;
  totalS -= hours*sph;
  long spm = 60;
  long minutes = totalS / spm;
  totalS -= minutes*spm;
  long seconds = totalS;
  byte ptr = 0;
  if(hours != 0){
    itoa(hours, buffer+ptr, 10);
    ptr = strlen(buffer);
    buffer[ptr++] = 'h';
  }
  if(minutes!= 0){
    itoa(minutes, buffer+ptr, 10);
    ptr = strlen(buffer);
    buffer[ptr++] = 'm';
  }
  itoa(seconds, buffer+ptr, 10);
  ptr = strlen(buffer);
  buffer[ptr++] = 's';
  buffer[ptr++] = '\0';
}



const byte displayBacklightPin = 9;
const byte displayPowerPin = 8;
const byte buzzerPin = 7;
const byte buttonPin = 2;


char buffer[20];

const byte STATE_STANDBY = 0;
const byte STATE_DISCHARGING = 1;
const byte STATE_STORAGE_ALERT = 2;
const byte STATE_ACTIVE = 3;
const byte STATE_SLEEP = 4;
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
}

void loop() {
  if(state == STATE_DEBUG){
    Display_Loop_Debug();
  }
  else{
    Display_Loop();
    buttonLoop();
    backlightLoop();
  }

  if(state == STATE_STANDBY){
    //change mode from standby to active by button
    if(isButtonPressedNow()){
      unsigned long st = millis();
      while(isButtonPressedNow() && millis() - st < 3000) Display_Loop();
      if(isButtonPressedNow()){
        state = STATE_ACTIVE;
        stateSetTime = millis();
        enableLowPowerOutput();
        buzzerBeep();
        delay(500);
        enableHighPowerOutput();
      }
    }
  }
  else if(state == STATE_ACTIVE){
    //change mode from active to standby by button
    if(isButtonPressedNow()){
      unsigned long st = millis();
      while(isButtonPressedNow() && millis() - st < 3000) Display_Loop();
      if(isButtonPressedNow()){
        state = STATE_STANDBY;
        disableLowPowerOutput();
        stateSetTime = millis();
        buzzerBeep();
        delay(500);
        disableHighPowerOutput();
      }
    }
  }
  
}





// useful functions

void enableLowPowerOutput(){
  relay1On();
  relay3On(); //debug
  relay4On(); //debug
}
void disableLowPowerOutput(){
  relay1Off();
}

void enableHighPowerOutput(){
  relay2On();
}
void disableHighPowerOutput(){
  relay2Off();
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

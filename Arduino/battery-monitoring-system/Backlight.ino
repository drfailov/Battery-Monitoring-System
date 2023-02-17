byte backlightState = 0;
unsigned long lastBacklightAction = 0;


byte backlightFullLevel = 200;
unsigned long backlightDimTimeout = 15000;//ms
byte backlightDimLevel = 20;
unsigned long backlightOffTimeout = 60000;//ms
byte backlightVeryDimLevel = 1;
byte backlightOffLevel = 0;

void backlightInit(){
  for(byte i=0; i<backlightFullLevel; i++){ //turn on backlight
    analogWrite(displayBacklightPin, backlightState=i);
    delay(1);
  }
}

void backlightLoop(){
  if(isButtonPressedNow())
    backlightRegisterClick();
  if(millis() - lastBacklightAction < backlightDimTimeout)
    analogWrite(displayBacklightPin, backlightState=backlightFullLevel);
    
  if(millis() - lastBacklightAction > backlightDimTimeout)
    if(backlightState > backlightDimLevel)
      analogWrite(displayBacklightPin, (backlightState-=3));

  if(state == STATE_STANDBY){
    if(millis() - lastBacklightAction > backlightOffTimeout)
      if(backlightState > backlightOffLevel)
        analogWrite(displayBacklightPin, --backlightState);
  }
  
  if(state == STATE_ACTIVE){
    if(millis() - lastBacklightAction > backlightOffTimeout)
      if(backlightState > backlightVeryDimLevel)
        analogWrite(displayBacklightPin, --backlightState);
  }
}
void backlightRegisterClick(){
  lastBacklightAction = millis();
}

bool buttonLastState = false;
const byte buttonPin = 2;
unsigned long buttonLastPress = 0;
long buttonContinuousClicks = 0;


void buttonLoop(){
  bool buttonState = isButtonPressedNow();
  if(buttonState && !buttonLastState){
    buzzerBeepShort();
  }
  buttonLastState = buttonState;
  attachInterrupt(digitalPinToInterrupt(buttonPin), pressed, FALLING);
}

bool isButtonPressedNow(){
  pinMode(buttonPin, INPUT_PULLUP);
  return digitalRead(buttonPin) == LOW;
}

bool pressed(){
  if(millis() - buttonLastPress > 10/*ms*/){
    if(buttonContinuousClicks < 10)
      buzzerBeepShort();
    backlightRegisterClick();
    
    if(millis() - buttonLastPress < 300/*ms*/)
      buttonContinuousClicks++;
    else
      buttonContinuousClicks = 0;
      
    if(buttonContinuousClicks == 10){
      resetPowerCounter();
      message(F("RESET Wh_S_RESET"));
      buzzerLongBeep();
    }
  }
  buttonLastPress = millis();
}

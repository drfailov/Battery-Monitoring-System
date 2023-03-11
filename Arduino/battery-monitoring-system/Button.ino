
//button:
//on-off (3000-5000ms)
//backlight-on / backlight-auto (5000-7000ms)
//reset power meter (7000-9000ms)
//reboot (9000-11000ms)


const byte buttonPin = 2;
bool buttonLastState = false;
unsigned long buttonActionDownTime = -1;
unsigned long buttonLoopLastTime = 0;

void buttonLoop(){
  bool buttonState = isButtonPressedNow();
  if(buttonState && !buttonLastState){ //DOWN ACTION
    buzzerBeepShort();
    buttonActionDownTime = millis();
  }
  if(!buttonState && buttonLastState){ //UP ACTION
    if(getButtonPressingTime() >= 2000 && getButtonPressingTime() < 5000){ //TURN ON / OFF
      if(state == STATE_STANDBY)
        activeMode();
      else if(state == STATE_ACTIVE){
        standbyMode();
      }
    }
    if(getButtonPressingTime() >= 5000 && getButtonPressingTime() < 7000){ //BACKLIGHT ON / AUTO
      if(isBacklightForceOn()){
        setBacklightForceOn(false);
        message(F("BACKLIGHT SET AUTO"));
      }
      else{
        setBacklightForceOn(true);
        message(F("BACKLIGHT SET ON"));
      }
      buzzerPlaySomeBeep();
    }
    if(getButtonPressingTime() >= 7000 && getButtonPressingTime() < 9000){ //RESET Wh
      resetPowerCounter();
      message(F("RESET Wh_S_RESET"));
      buzzerBeep();
    }
    if(getButtonPressingTime() >= 9000 && getButtonPressingTime() < 11000){ //REBOOT
      message(F("REBOOT"));
      buzzerBeep();
      resetFunc();
    }

    
  }
  if(!buttonState){  //NOT PRESSED
    buttonActionDownTime = -1;
  }
  if(buttonState){  //PRESSED
    long buttonPressingTimeOnLastLoop = getButtonPressingTime() - (millis()-buttonLoopLastTime);
    if(getButtonPressingTime() >= 2000 && buttonPressingTimeOnLastLoop < 2000)
      buzzerBeepShort();
    if(getButtonPressingTime() >= 5000 && buttonPressingTimeOnLastLoop < 5000)
      buzzerBeepShort();
    if(getButtonPressingTime() >= 7000 && buttonPressingTimeOnLastLoop < 7000)
      buzzerBeepShort();
    if(getButtonPressingTime() >= 9000 && buttonPressingTimeOnLastLoop < 9000)
      buzzerBeepShort();
  }
  buttonLastState = buttonState;
  buttonLoopLastTime = millis();
  attachInterrupt(digitalPinToInterrupt(buttonPin), pressed, FALLING);


  
//  if(isButtonPressedNow()){    //change mode from standby to active by button
//      unsigned long st = millis();
//      while(isButtonPressedNow() && millis() - st < 3000) Display_Loop();
//      if(isButtonPressedNow()){
//        activeMode();
//        return;
//      }
//    }
}






bool isButtonPressedNow(){
  pinMode(buttonPin, INPUT_PULLUP);
  return digitalRead(buttonPin) == LOW;
}
/*How much time button is pressed since it down.
If button is not pressed, result is -1*/
long getButtonPressingTime(){
  if(buttonActionDownTime == -1)
    return -1;
  return millis() - buttonActionDownTime;
}

bool pressed(){
//  if(millis() - buttonLastPress > 10/*ms*/){
//    if(buttonContinuousClicks < 10)
//      buzzerBeepShort();
    backlightRegisterClick();
//    
//    if(millis() - buttonLastPress < 300/*ms*/)
//      buttonContinuousClicks++;
//    else
//      buttonContinuousClicks = 0;
//      
//    if(buttonContinuousClicks == 10){
//      resetPowerCounter();
//      message(F("RESET Wh_S_RESET"));
//      buzzerLongBeep();
//    }
//  }
//  buttonLastPress = millis();
}

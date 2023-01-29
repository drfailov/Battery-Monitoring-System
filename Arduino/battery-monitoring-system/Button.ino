bool buttonLastState = false;


void buttonLoop(){
  bool buttonState = isButtonPressedNow();
  if(buttonState && !buttonLastState){
    buzzerBeepShort();
  }
  buttonLastState = buttonState;
  
}

bool isButtonPressedNow(){
  pinMode(buttonPin, INPUT_PULLUP);
  return digitalRead(buttonPin) == LOW;
}


const byte buzzerPin = 7;

const int BUZZER_ACTION_NONE = 0;
const int BUZZER_ACTION_SHORT = 1;
const int BUZZER_ACTION_BEEP = 2;
const int BUZZER_ACTION_LONG = 3;

int buzzerAction = BUZZER_ACTION_NONE;

void buzzerInit(){
  pinMode(buzzerPin, OUTPUT);
  for(int i=0; i<3; i++){
    digitalWrite(buzzerPin, HIGH);
    delay(5);
    digitalWrite(buzzerPin, LOW);
    delay(80);
  }
}

void buzzerLoop(){
  if(buzzerAction == BUZZER_ACTION_SHORT){
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, HIGH);
    delay(5);
    digitalWrite(buzzerPin, LOW);
    buzzerAction = BUZZER_ACTION_NONE;
  }
  
  if(buzzerAction == BUZZER_ACTION_BEEP){
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    buzzerAction = BUZZER_ACTION_NONE;
  }
  
  if(buzzerAction == BUZZER_ACTION_LONG){
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
    buzzerAction = BUZZER_ACTION_NONE;
  }
}

void buzzerBeepShort(){
  //buzzerAction = BUZZER_ACTION_SHORT;
  tone(buzzerPin, 1000, 5);
}
void buzzerBeep(){
  //buzzerAction = BUZZER_ACTION_BEEP;
  tone(buzzerPin, 1000, 100);
}
void buzzerLongBeep(){
  //buzzerAction = BUZZER_ACTION_LONG;
  tone(buzzerPin, 1000, 600);
}
void buzzerPlayOff(){
  tone(buzzerPin, 3000, 50);
  delay(70);
  tone(buzzerPin, 2000, 100);
  delay(120);
  tone(buzzerPin, 1000, 50);
  delay(60);
  tone(buzzerPin, 1000, 50);
  delay(60);
  tone(buzzerPin, 1000, 50);
  delay(60);
  tone(buzzerPin, 700, 200);
}
void buzzerPlaySomeBeep(){
  tone(buzzerPin, 1000, 50);
  delay(60);
  tone(buzzerPin, 1000, 50);
  delay(60);
  tone(buzzerPin, 1000, 50);
}
void buzzerPlayOn(){
  tone(buzzerPin, 1000, 200);
  delay(220);
  tone(buzzerPin, 2000, 100);
  delay(120);
  tone(buzzerPin, 3000, 50);
}

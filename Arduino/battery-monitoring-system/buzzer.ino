void buzzerInit(){
  pinMode(buzzerPin, OUTPUT);
  for(int i=0; i<3; i++){
    digitalWrite(buzzerPin, HIGH);
    delay(5);
    digitalWrite(buzzerPin, LOW);
    delay(80);
  }
}

void buzzerBeepShort(){
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  delay(5);
  digitalWrite(buzzerPin, LOW);
}
void buzzerBeep(){
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
}

void buzzerLongBeep(){
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

const int pinRelay1 = 5;
const int pinRelay2 = 4;
const int pinRelay3 = 6;
const int pinRelay4 = 10;

void relaySetup(){
    relay1Off();
    relay2Off();
    relay3Off();
    relay4Off();
}

void relay1Off(){
  pinMode(pinRelay1, OUTPUT);
  digitalWrite(pinRelay1, LOW);
}
void relay1On(){
  pinMode(pinRelay1, OUTPUT);
  digitalWrite(pinRelay1, HIGH);
}



void relay2Off(){
  pinMode(pinRelay2, OUTPUT);
  digitalWrite(pinRelay2, LOW);
}
void relay2On(){
  pinMode(pinRelay2, OUTPUT);
  digitalWrite(pinRelay2, HIGH);
}



void relay3Off(){
  pinMode(pinRelay3, OUTPUT);
  digitalWrite(pinRelay3, LOW);
}
void relay3On(){
  pinMode(pinRelay3, OUTPUT);
  digitalWrite(pinRelay3, HIGH);
}



void relay4Off(){
  pinMode(pinRelay4, OUTPUT);
  digitalWrite(pinRelay4, LOW);
}
void relay4On(){
  pinMode(pinRelay4, OUTPUT);
  digitalWrite(pinRelay4, HIGH);
}

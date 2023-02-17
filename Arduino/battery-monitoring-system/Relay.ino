const int pinRelay1 = 5;
const int pinRelay2 = 4;
const int pinRelay3 = 6;
const int pinRelay4 = 3;
bool relay1State;
bool relay2State;
bool relay3State;
bool relay4State;

void relaySetup(){
    relay1Off();
    relay2Off();
    relay3Off();
    relay4Off();
}

void relay1Off(){
  pinMode(pinRelay1, OUTPUT);
  digitalWrite(pinRelay1, LOW);
  relay1State = false;
}
void relay1On(){
  pinMode(pinRelay1, OUTPUT);
  digitalWrite(pinRelay1, HIGH);
  relay1State = true;
}
bool getRelay1State(){
  return relay1State;
}



void relay2Off(){
  pinMode(pinRelay2, OUTPUT);
  digitalWrite(pinRelay2, LOW);
  relay2State = false;
}
void relay2On(){
  pinMode(pinRelay2, OUTPUT);
  digitalWrite(pinRelay2, HIGH);
  relay2State = true;
}
bool getRelay2State(){
  return relay2State;
}



void relay3Off(){
  pinMode(pinRelay3, OUTPUT);
  digitalWrite(pinRelay3, LOW);
  relay3State = false;
}
void relay3On(){
  pinMode(pinRelay3, OUTPUT);
  digitalWrite(pinRelay3, HIGH);
  relay3State = true;
}
bool getRelay3State(){
  return relay3State;
}



void relay4Off(){
  pinMode(pinRelay4, OUTPUT);
  digitalWrite(pinRelay4, LOW);
  relay4State = false;
}
void relay4On(){
  pinMode(pinRelay4, OUTPUT);
  digitalWrite(pinRelay4, HIGH);
  relay4State = true;
}
bool getRelay4State(){
  return relay4State;
}

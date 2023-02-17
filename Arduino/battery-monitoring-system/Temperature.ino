// Thermistor Example #3 from the Adafruit Learning System guide on Thermistors 
// https://learn.adafruit.com/thermistor/overview by Limor Fried, Adafruit Industries
// MIT License - please keep attribution and consider buying parts from Adafruit

// which analog pin to connect
#define PIN_THERMISTOR A6          
#define PIN_THERMISTOR_POWER A3  
#define PIN_THERMISTOR2 A7         
#define PIN_THERMISTOR2_POWER A2
//PIN_THERMISTOR
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    

int samples[NUMSAMPLES];


float getBatteryTemp(){
  pinMode(PIN_THERMISTOR_POWER, OUTPUT);
  digitalWrite(PIN_THERMISTOR_POWER, HIGH);
  
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(PIN_THERMISTOR);
   delay(10);
  }
  
  pinMode(PIN_THERMISTOR_POWER, INPUT);
  
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
  average = 1024-average;//replace GND and +5V

//  Serial.print("Average analog reading "); 
//  Serial.println(average);
  
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
//  Serial.print("Thermistor resistance "); 
//  Serial.println(average);
  
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  
//  Serial.print("Temperature: "); 
//  Serial.println(steinhart);
  return steinhart;
}

float getInternalTemp(){
  //float temperature=(ADCW – 324.31f)/1.22f;
  //return temperature;
  ADMUX = 0xC8; // turn on internal reference, right-shift ADC buffer, ADC channel = internal temp sensor
  delay(10);  // wait a sec for the analog reference to stabilize
  
  ADCSRA |= _BV(ADSC); // start the conversion
  while (bit_is_set(ADCSRA, ADSC)); // ADSC is cleared when the conversion finishes
  return (ADCL | (ADCH << 8)) - 342; // combine bytes & correct for temp offset (approximate)} 
}


float getShuntTemp(){
  pinMode(PIN_THERMISTOR2_POWER, OUTPUT);
  digitalWrite(PIN_THERMISTOR2_POWER, HIGH);
  
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(PIN_THERMISTOR2);
   delay(10);
  }
  
  pinMode(PIN_THERMISTOR2_POWER, INPUT);
  
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
  //average = 1024-average;//replace GND and +5V

//  Serial.print("Average analog reading "); 
//  Serial.println(average);
  
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
//  Serial.print("Thermistor resistance "); 
//  Serial.println(average);
  
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  
//  Serial.print("Temperature: "); 
//  Serial.println(steinhart);
  return steinhart;
}

byte state = 0;
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
  Display_Setup();
}

void loop() {
  Display_Loop();
  
  
}

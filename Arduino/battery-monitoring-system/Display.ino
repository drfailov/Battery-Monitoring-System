#include <U8glib.h>                                            // Подключаем библиотеку U8glib
U8GLIB_ST7920_128X64_1X u8g(12);                               // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI



void Display_Setup(){
  pinMode(displayPowerPin, OUTPUT);
  digitalWrite(displayPowerPin, HIGH);
  u8g.firstPage();                                           
  do{  
    u8g.setColorIndex(1);
    u8g.drawBox(0,0,128,64);
  } while(u8g.nextPage());
}

void Display_Loop(){
    float temperatureBattery = getBatteryTemp();
    float temperatureShunt = getShuntTemp();
    float cell1Voltage = getCell1Voltage();
    float cell2Voltage = getCell2Voltage();
    float cell3Voltage = getCell3Voltage();
    int16_t systemCurrent = getSystemCurrent_mA();
    int16_t loadCurrentRaw = getCurrentRaw();
    long loadCurrent = getCurrent_mA(loadCurrentRaw);
    
    u8g.firstPage();                                           
    do{  
        //==== STATE
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/0, /*y*/39);
        if(state == STATE_STANDBY)
          u8g.print("STANDBY");
        if(state == STATE_ACTIVE)
          u8g.print("ACTIVE");
        ttostr(millis()-stateSetTime, buffer);
        u8g.print(" (");
        u8g.print(buffer);
        u8g.print(")");

        //==== LOAD VOLTAGE
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/35, /*y*/5);    
        u8g.print(cell3Voltage, 2);   
        u8g.print("V");  
        
        //==== LOAD CURRENT
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/35, /*y*/12);
        u8g.print(loadCurrent, 10);   
        u8g.print("mA");  
        if(state == STATE_ACTIVE && millis()-getLastTimeCurrentNoZero() > 1000L*30L /*30sec*/){
          ttostr(millis()-getLastTimeCurrentNoZero(), buffer); //draw time of inactivity if inactive for 10 min
          u8g.print(" (");
          u8g.print(buffer);
          u8g.print(")");
        }
        
        //==== POWER METER
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/35, /*y*/19);
        u8g.print("R:"); 
        u8g.print(getWhSinseReset(), 3);   
        u8g.print("Wh"); 
        
        //==== POWER METER
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/35, /*y*/26);
        u8g.print("F:"); 
        u8g.print(getWhSinseFullCharge(), 3);   
        u8g.print("Wh"); 
        

         
        //==== INPUT
        u8g.setFont(u8g_font_babyr);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17
        u8g.setPrintPos(0, 5);
        u8g.print("INPUT");
        u8g.setFont(u8g_font_tpssbn);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17
        u8g.setPrintPos(0, 20);
        float inWattage = 0;
        if(loadCurrent > 0)
          inWattage  = cell3Voltage * loadCurrent / 1000; 
        u8g.print(inWattage , 0);
        u8g.setFont(u8g_font_babyr);
        u8g.print("W");
  
        //==== OUTPUT
        u8g.setFont(u8g_font_babyr);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17
        u8g.setPrintPos(100, 5);
        u8g.print("OUTPUT");
        u8g.setFont(u8g_font_tpssbn);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17
        u8g.setPrintPos(100, 20);
        float outWattage = 0;
        if(loadCurrent < 0)
          outWattage = cell3Voltage * -loadCurrent / 1000; 
        u8g.print(outWattage, 0);
        u8g.setFont(u8g_font_babyr);
        u8g.print("W"); 

        //==== TEMPERATURE
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/0, /*y*/46);
        u8g.print("BATT: ");  
        u8g.print(temperatureBattery, 1);   
        u8g.print(" C");  
        u8g.setPrintPos(/*x*/0, /*y*/53);
        u8g.print("SHUNT: ");  
        u8g.print(temperatureShunt, 1);   
        u8g.print(" C");  
        
        //==== BALANCE
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/106, /*y*/39);
        u8g.print(cell1Voltage, 2);
        u8g.print("v");
        u8g.setPrintPos(/*x*/106, /*y*/46);
        u8g.print((cell2Voltage-cell1Voltage), 2);   
        u8g.print("v");
        u8g.setPrintPos(/*x*/106, /*y*/53);
        u8g.print((cell3Voltage-cell2Voltage), 2);   
        u8g.print("v");
          
        //==== MESSAGE
        u8g.setColorIndex(1);
        //u8g.drawLine(0, 55, 128, 55);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/0, /*y*/63);
        ttostr(millis()-messageSetTime, buffer);
        u8g.print("");
        u8g.print(buffer);
        u8g.print(": ");
        u8g.print(messageText);   

        //==== STORAGE DISCHAGRE
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/122, /*y*/64);
        if(isEnabledStorageDischarge())
          u8g.print("S");     

        //==== HIGH POWER
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/122, /*y*/64);
        if(isEnabledHighPowerOutput())
          u8g.print("H"); 
    } while(u8g.nextPage());
  
    
}















void Display_Loop_Debug(){
  // Всё что выводится на дисплей указывается в цикле: u8g.firstPage(); do{ ... команды ... }while(u8g.nextPage());    

    
        
    u8g.firstPage();                                           
    do{  
      u8g.setColorIndex(1);
      u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n

      u8g.setPrintPos(/*x*/0, /*y*/8);
      u8g.print("RAW");

      


      //demo
//      u8g.setColorIndex(1);
//      u8g.setPrintPos(/*x*/0, /*y*/64);
//      u8g.setFont(u8g_font_fub17n);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17    u8g_font_fub17r u8g_font_fub17n
//      u8g.print("1 ");
//      u8g.setFont(u8g_font_tpssbr);
//      u8g.print(" 2");
//      u8g.setFont(u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n
//      u8g.print(millis());   
    } while(u8g.nextPage());
}

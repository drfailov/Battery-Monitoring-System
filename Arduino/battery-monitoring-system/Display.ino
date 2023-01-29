#include <U8glib.h>                                            // Подключаем библиотеку U8glib
U8GLIB_ST7920_128X64_1X u8g(12);                               // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI



void Display_Setup(){
  pinMode(displayPowerPin, OUTPUT);
  digitalWrite(displayPowerPin, HIGH);
  
}

void Display_Loop(){
    float temperature = getTemp();
    float cell1Voltage = getCell1Voltage();
    float cell2Voltage = getCell2Voltage();
    float cell3Voltage = getCell3Voltage();
    int16_t systemCurrent = getSystemCurrent_mA();
    int16_t loadCurrentRaw = getCurrentRaw();
    long loadCurrent = getCurrent_mA(loadCurrentRaw);
    
    u8g.firstPage();                                           
    do{  
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/0, /*y*/20);
        if(state == STATE_STANDBY)
          u8g.print("STANDBY");
        if(state == STATE_ACTIVE)
          u8g.print("ACTIVE");
        ttostr(millis()-stateSetTime, buffer);
        u8g.print(" (");
        u8g.print(buffer);
        u8g.print(")");

        //balance
        u8g.setColorIndex(1);
        u8g.setFont(/*font*/u8g_font_babyr);                       //шрифт u8g_font_tpssbr         u8g_font_babyr         u8g_font_fub17n      
        u8g.setPrintPos(/*x*/110, /*y*/48);
        u8g.print(cell1Voltage, 2);
        u8g.setPrintPos(/*x*/110, /*y*/56);
        u8g.print((cell2Voltage-cell1Voltage), 2);   
        u8g.setPrintPos(/*x*/110, /*y*/64);
        u8g.print((cell3Voltage-cell2Voltage), 2);   


        //load current
        u8g.setPrintPos(/*x*/0, /*y*/64);
        u8g.print(loadCurrentRaw, 10);   
        u8g.setPrintPos(/*x*/0, /*y*/54);
        u8g.print(loadCurrent, 10);   
        u8g.print(" mA");   


        //system current
        u8g.setPrintPos(/*x*/0, /*y*/10);
        u8g.print(systemCurrent, 10);   
        u8g.print(" mA");  

        //temperature
        u8g.setPrintPos(/*x*/60, /*y*/10);
        u8g.print(temperature, 1);   
        u8g.print(" *C");  
        
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

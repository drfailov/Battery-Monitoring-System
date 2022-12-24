#include <U8glib.h>                                            // Подключаем библиотеку U8glib
U8GLIB_ST7920_128X64_1X u8g(12);                               // Создаём объект u8g для работы с дисплеем, указывая номер вывода CS для аппаратной шины SPI
#define backlightPin 9


void Display_Setup(){
  for(byte i=0; i<255; i++){ //turn on backlight
    analogWrite(backlightPin, i);
    delay(2);
  }
}

void Display_Loop(){
  // Всё что выводится на дисплей указывается в цикле: u8g.firstPage(); do{ ... команды ... }while(u8g.nextPage());          
    u8g.firstPage();                                           
    do{  




      //demo
      u8g.setColorIndex(1);
      u8g.setPrintPos(/*x*/0, /*y*/64);
      u8g.setFont(u8g_font_fub17n);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17    u8g_font_fub17r u8g_font_fub17n
      u8g.print("1 ");
      u8g.setFont(u8g_font_tpssbr);
      u8g.print(" 2");
      u8g.setFont(u8g_font_babyr);                       //шрифт u8g_font_tpssb         u8g_font_baby         u8g_font_fub17
      u8g.print(millis());   
    } while(u8g.nextPage());

    
}


//do analogread twice with 10ms delay
//https://forum.arduino.cc/t/adc-voltmeter-linearity-problems-solved/299805/2

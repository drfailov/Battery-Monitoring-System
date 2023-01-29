/*How to make calibration:
DISCONNECT USB port, power Arduino only by 12W power source.
DISCONNECT cell3 from Vin port on Arduino.
Connect laboratory power supply and precice multimeter to GND and cell leads.
Select voltage on laboratiry power supply, write down precise voltage measured by voltmeter, write down raw value from screen.
In this way fill down table for all 3 cells and for voltages with step 2v.
After calibration connect cell3 to Vin of arduino.*/

float cell1Calibration[][2] = { //{mv, raw}
  {0, 0},
  {2001, 129},
  {4000, 259},
  {6006, 390},
  {8002, 521},
  {10008, 652},
  {12012, 783},
  {14002, 913},
  {16002, 1024}
};

float cell2Calibration[][2] = { //{mv, raw}
  {0, 0},
  {2002, 124},
  {4000, 250},
  {6007, 377},
  {8002, 503},
  {10008, 629},
  {12012, 756},
  {14002, 881},
  {16290, 1024}
};

float cell3Calibration[][2] = { //{mv, raw}
  {0, 0},
  {2002, 125},
  {4002, 251},
  {6008, 378},
  {8003, 505},
  {10008, 632},
  {12014, 760},
  {14005, 886},
  {16210, 1024}
};

float linearInterpolate(float y, float data[][2], byte tableLength){
  float x0, x1, y0, y1;
  for (int i = 0; i < tableLength-1; i++)
  {
    if (y > data[i][1] && y < data[i + 1][1])
    {
      y0 = data[i][1];  //lower bound
      y1 = data[i + 1][1]; //upper bound
      x0 = data[i][0];
      x1 = data[i + 1][0];
      return (x0 + ((x1 - x0) * ((y - y0) / (y1 - y0))));
    }
  }
}



//699 = 11309
//((699/1023)*5148)*(11309/3400) = 11699.9866792
//699/1023 = 0.68328445747
//0.68328445747*5148 = 3517.54838706
//11309/3400 = 3.32617647059
//3517.54838706 * 3.32617647059 = 11699.9866792
//699 * ((5148*11309) / (1024*3400))
//const float arefVolageOnBattery = 5029;  //mv
//const float arefVolageOnUsb = 5148; //mv

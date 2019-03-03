#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT 10
#define OE  9
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false , 64);

byte last[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

#define RED_PEAK 10
#define BLUE_PEAK 5

uint16_t green = matrix.Color333(0, 255, 0);
uint16_t yellow = matrix.Color333(255, 255, 0);
uint16_t red = matrix.Color333(255, 0, 0);
uint16_t black = matrix.Color333(0, 0, 0);
uint16_t blue = matrix.Color333(0, 0, 50);

String sep = ":";

void setup() {
  Serial.begin(57600);    //USB
  Serial1.begin(57600);   //screen
  Serial3.begin(38400);   //BT
  matrix.begin();
  Serial.println("Starting");
  matrix.drawRect(0,0,64 ,32, matrix.Color333(7 ,0 ,0));
}

void loop() {
  while (Serial3.available() > 0) {
    
    String in = Serial3.readStringUntil('\n');

    int f = in.substring(0, in.indexOf(sep)).toInt();
    int ff = in.substring(in.indexOf(sep) + sep.length()).toInt();
  
    if (f < 31 && ff < 16) {  
      int x0 = f;

      if (ff > 0) {
        Serial.print("Got: ");
        Serial.print(f);
        Serial.print(' ');
        Serial.println(ff);
      }
  
      uint16_t color;
  
      if (ff > last[f]) {
        for(int y = last[f]; y <= ff; y++) {
          int x = 61 - 2*x0;
          color = y > RED_PEAK ? yellow : blue;
          matrix.drawPixel(x, y*2, color);
          matrix.drawPixel(x, y*2+1, color);
          matrix.drawPixel(x+1, y*2, color);
          matrix.drawPixel(x+1, y*2+1, color);  
        }
      } else if (last[f] > ff) {
        color = black;
        
        for(int y = last[f]; y > ff; y--) {
          matrix.drawPixel(61 - 2*x0, y*2, color);
          matrix.drawPixel(61 - 2*x0, y*2+1, color);
          matrix.drawPixel(62 - 2*x0, y*2, color); 
          matrix.drawPixel(62 - 2*x0, y*2+1, color);
          
        }
      }

      matrix.swapBuffers(false);
  
      last[f] = ff;
    }
  }
}

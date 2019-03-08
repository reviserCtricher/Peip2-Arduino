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
// Set a wide range of usable colors
uint16_t green = matrix.Color333(0, 255, 0);
uint16_t yellow = matrix.Color333(255, 255, 0);
uint16_t red = matrix.Color333(255, 0, 0);
uint16_t black = matrix.Color333(0, 0, 0);
uint16_t blue = matrix.Color333(0, 0, 50);

String sep = ":";

int buffer2=0; // initialize the second and third versions buffer
int maxi=0; // max sample for second and third versions

void setup() {
  Serial.begin(57600);    //Comes for debugging
  Serial1.begin(57600);   //Screen
  Serial3.begin(38400);   //BT
  matrix.begin();         //Start display
  Serial.println("Starting");
}

void loop() {
  while (Serial3.available() > 0) {  //get FFT data from BT 
    
    String in = Serial3.readStringUntil('\n');

    int f = in.substring(0, in.indexOf(sep)).toInt();  //stands for the first part of the data (before ":") frequency 
    int ff = in.substring(in.indexOf(sep) + sep.length()).toInt(); //stands for the second part of data : range 
  
    if (f < 31 && ff < 16) {   //set for smaller display
      int x0 = f;

      if (ff > 0) {     //if range not null
        Serial.print("Got: ");
        Serial.print(f); //x
        Serial.print(' ');
        Serial.println(ff); //f(x)
      }
  
      uint16_t color;
      
      // Select which display you want by uncommenting the correct version

       //Programme d'origine - Version I
       
      if (ff > last[f]) {
        for(int y = last[f]; y <= ff; y++) {
            int x = 61 - 2*x0;
            color = y > RED_PEAK ? yellow : blue; //set the color of the max_range
            matrix.drawRect(x , y*2+1 , 2 , 2 ,color);
        }
      } else if (last[f] > ff) {
        color = black;
        
        for(int y = last[f]; y > ff; y--) {
            matrix.drawRect(61 - 2*x0 , y*2+1 , 2 , 2 ,color);
        
        }
      } 
       matrix.swapBuffers(false);
  
      last[f] = ff;
      
/**
  
      // Version II - Affiche 8 cercles
      if (ff > last[f]) {
          if (ff>maxi) 
            {maxi=ff;}
          buffer2++;
          if (buffer2 == 8) {
            buffer2 = 0;
            color = maxi > RED_PEAK ? yellow : blue;
            int x = 61 - 2*x0;
            x=(x-3)/8;
            matrix.fillCircle(x*7+7,(x%2)*12+10,6,matrix.Color333(0,0,0));
            matrix.fillCircle(x*7+7,(x%2)*12+10,maxi/3,color);
            maxi=0;}
          }
   
  **/
   // Version III - Psyché
   /**
      if (ff > last[f]) {
          if (ff>maxi) 
            {maxi=ff;}
          buffer2 ++;
          if (buffer2 == 8) {
            buffer2 = 0;
            int rcol1=random(0,7);
            int rcol2=random(0,7);
            int rcol3=random(0,7);
            int color=matrix.Color333(rcol1,rcol2,rcol3);
            
            int x = 61 - 2*x0;
            x=(x-3)/8;
            matrix.fillCircle(x*7+7,(x%2)*12+10,8,matrix.Color333(0,0,0));
            matrix.fillCircle(x*7+7,(x%2)*12+10,maxi/1.25,color);
            maxi=0;}
          }
      
**/
     
      
    }
  }
}

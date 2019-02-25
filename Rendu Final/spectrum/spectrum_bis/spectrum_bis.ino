/*
 * Arduino Spectrum Analizer
 * 
 * learnelectronics
 * 27 April 2017
 * black magic stolen from CBM80Amiga
 * 
 * www.youtube.com/c/learnelectronics
 * arduino1069@gmail.com
 * 
 * Fix_FFT library available @ https://github.com/kosme/arduinoFFT
 */


#include "fix_fft.h"                                  //library to perfom the Fast Fourier Transform
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT 10
#define OE  9
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false , 64);


#include <Adafruit_GFX.h>                             //graphics library for OLED


char im[128], data[128];                              //variables for the FFT
char x = 0, ylim = 31;                                //variables for drawing the graphics
int i = 0, val;                                       //counters

void setup()
{
  Serial.begin(9600);                                 //serial comms for debuging
  Serial1.begin(57600);
  Serial3.begin(38400);
  matrix.begin();
 
 
 
 
};

void loop()
{
  int min=1024, max=0;                                //set minumum & maximum ADC value
  for (i = 0; i < 128; i++) {                         //take 128 samples
    val = analogRead(A8) ;                             //get audio from Analog serial 
    Serial.println(val , DEC);
    data[i] = val / 4 - 128;                          //each element of array is val/4-128
    im[i] = 0;                                        //
    if(val>max) max=val;                              //capture maximum level
    if(val<min) min=val;                              //capture minimum level
  };
    
  fix_fft(data, im, 7, 0);                            //perform the FFT on data
  
  matrix.fillRect
  ( 0, 0 , 64 ,32 ,matrix.Color333(0, 0, 0));                           //clear display

  for(int i=2 ; i<4; i++){
    int maxi=0;
    for(int j=i*16+1 ; j<i*16+17 ; j++){
      int dat = sqrt(data[j] * data[j] + im[j] * im[j]);
      if(dat>maxi){maxi=dat;}
      
    }
    if(maxi>7){
        matrix.fillCircle((i-2)*32+15 , 15 , maxi/2 , matrix.Color333(0 , 0 ,7));
        matrix.fillCircle((i-2)*32+15 , 15 , 4 , matrix.Color333(0 , 7 ,0));
      }
      else{
        matrix.fillCircle((i-2)*32+15 , 15 , maxi/2 , matrix.Color333(0 , 7 ,0));
      }
  }
}

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

//#include <SPI.h>                                      //SPI library
//#include <Wire.h>                                     //I2C library for OLED

#include <Adafruit_GFX.h>                             //graphics library for OLED

//#include <Adafruit_SSD1306.h>                         //OLED driver

//#define OLED_RESET 4                                  //OLED reset, not hooked up but required by library
//Adafruit_SSD1306 display(OLED_RESET);                 //declare instance of OLED library called display

char im[128], data[128];                              //variables for the FFT
char x = 0, ylim = 60;                                //variables for drawing the graphics
int i = 0, val;                                       //counters

void setup()
{
  Serial.begin(9600);                                 //serial comms for debuging
  Serial.begin(57600);
  Serial1.begin(57600);
  Serial3.begin(38400);
  matrix.begin();
  //display.begin(SSD1306_SWITCHCAPVCC,0x3C);           //begin OLED @ hex addy 0x3C
  //display.setTextSize(1);                             //set OLED text size to 1 (1-6)
  //display.setTextColor(WHITE);                        //set text color to white
  //display.clearDisplay();                             //clear display
  //analogReference(DEFAULT);                           // Use default (5v) aref voltage.
};

void loop()
{
  int min=1024, max=0;                                //set minumum & maximum ADC values

  while (Serial3.available() >0){
    for (i = 0; i < 128; i++) {                         //take 128 samples
      val = Serial3.read();                             //get audio from Analog serial 3
      data[i] = val / 4 - 128;                          //each element of array is val/4-128
      im[i] = 0;                                        //
      if(val>max) max=val;                              //capture maximum level
      if(val<min) min=val;                              //capture minimum level
    }
  };
    
  fix_fft(data, im, 7, 0);                            //perform the FFT on data
  
  //display.clearDisplay();                             //clear display
  for (i = 1; i < 64; i++) {                          // In the current design, 60Hz and noise
    int dat = sqrt(data[i] * data[i] + im[i] * im[i]);//filter out noise and hum
    matrix.drawLine(i*2 + x, ylim, i*2 + x, ylim - dat, matrix.Color333(7,7,7)); // draw bar graphics for freqs above 500Hz to buffer
  };                                                
  
};

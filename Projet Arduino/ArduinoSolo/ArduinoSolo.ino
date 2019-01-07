#include <arduinoFFT.h>

arduinoFFT FFT = arduinoFFT();


//Setup de l'ecran
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


// audio
float peaks[10] ;

int peak_hold_time = 1;  // how long before peak decays
int peak_age[];  // tracks how long peak has been stable, before decaying

// how wide each 'peak' band is, in fft bins
int binsperband = 10;
int peaksize; // how many individual peak bands we have (dep. binsperband)
float gain = 40; // in dB
float dB_scale = 2.0;  // pixels per dB

int buffer_size = 1024;  // also sets FFT size (frequency resolution)
float sample_rate = 22050;
int spectrum_height = 176; // determines range of dB shown

/**
 * MISC settings
 */

 String Stock =""
 boolean enable_32 = true;
 int freq_range_maxes[] { 50, 69, 94, 129, 178, 241, 331, 453, 620, 850, 1241, 1600, 2200, 3000, 4100, 5600 };
 int num_levels = enable_32 ? 32 : 16;
 int freq_array [ num_levels] ;
 int last_freq [num_levels];
 float freq_height[num_levels];  //avg amplitude of each freq band
 int i,g;
 float f;




void setup() {
  // setup affichage 
  Serial1.begin(57600);
  Serial3.begin(38400);
  matrix.begin();

  //setup traitement 
  //create an FFT object (depends of the library)
   peaksize = 1+Math.round(fft.specSize()/binsperband);
   peaks = new float[peaksize];
   peak_age = new int[peaksize];
}

void draw(){
    for(int k = 0; k < num_levels; k++){
    freq_array[k] = 0;
  }

  // perform a forward FFT on the samples in input buffer
  fft.forward(in.mix);
  
  // Frequency Band Ranges
  for (int fh = 0; fh < freq_range_maxes.length; fh++) {
    if (enable_32) {
      // Use the set of 16 frequency ranges and split them
      // evenly to create 32 ranges
      int min = fh == 0 ? 0 : freq_range_maxes[fh-1] + 1;
      int max = freq_range_maxes[fh];
      int diff = (max - min) / 2;
      
      int max1 = min + diff;
      int min2 = min + diff + 1;
      
      int fh1 = fh*2;
      int fh2 = fh*2+1;
      
      freq_height[fh1] = fft.calcAvg((float) min, (float) max1);
      freq_height[fh2] = fft.calcAvg((float) min2, (float) max);
    } else {
      int max = freq_range_maxes[fh];
      int min = fh == 0 ? 0 : freq_range_maxes[fh-1] + 1;
      freq_height[fh] = fft.calcAvg((float) min, (float) max);
    }
  }

  // Amplitude Ranges: if else tree
  for (int j = 0; j < num_levels; j++) {
         if (freq_height[j] < 200000 && freq_height[j] > 200) { freq_array[j] = 16; }
    else if (freq_height[j] <= 300 && freq_height[j] > 150)   { freq_array[j] = 15; }
    else if (freq_height[j] <= 250 && freq_height[j] > 125)   { freq_array[j] = 14; }
    else if (freq_height[j] <= 200 && freq_height[j] > 100)   { freq_array[j] = 13; }
    else if (freq_height[j] <= 160 && freq_height[j] > 90)    { freq_array[j] = 12; }
    else if (freq_height[j] <= 150 && freq_height[j] > 75)    { freq_array[j] = 11; }
    else if (freq_height[j] <= 140 && freq_height[j] > 65)    { freq_array[j] = 10; }
    else if (freq_height[j] <= 120 && freq_height[j] > 50)    { freq_array[j] = 9; }
    else if (freq_height[j] <= 50 && freq_height[j] > 45)     { freq_array[j] = 8; }
    else if (freq_height[j] <= 45 && freq_height[j] > 40)     { freq_array[j] = 7; }
    else if (freq_height[j] <= 40 && freq_height[j] > 35)     { freq_array[j] = 6; }
    else if (freq_height[j] <= 35 && freq_height[j] > 30)     { freq_array[j] = 5; }
    else if (freq_height[j] <= 30 && freq_height[j] > 15)     { freq_array[j] = 4; }
    else if (freq_height[j] <= 15 && freq_height[j] > 10)     { freq_array[j] = 3; }
    else if (freq_height[j] <= 10 && freq_height[j] > 5)      { freq_array[j] = 2; }
    else if (freq_height[j] <= 5 && freq_height[j] >= 1)      { freq_array[j] = 1; }
    else if (freq_height[j] < 1 )                             { freq_array[j] = 0; }
  }
  
  for (i = 0; i < num_levels; i++) {
    
    if (freq_array[i] != last_freq[i]) {
      String out = i + ":" + freq_array[i] + "\n";
      println(out.trim());
      Stock.write(out);
      last_freq[i] = freq_array[i];
      
      if (i % 3 == 0)
        delay(3);
    }
  }
  
  delay(2); //delay for and timing
}

 void loop() {
  
  String in = Stock.readStringUntil('\n');
  int f = in.substring(0, in.indexOf(sep)).toInt();
  int ff = in.substring(in.indexOf(sep) + sep.length()).toInt();
  if (f < 31 && ff < 16) {  
      int x0 = f;
      
      uint16_t color;
  
      if (ff > last[f]) {
        for(int y = last[f]; y <= ff; y++) {
          int x = 47 - x0;
          color = y > RED_PEAK ? yellow : blue;
          matrix.drawPixel(x, y*2 - 1, color); 
        }
      } else if (last[f] > ff) {
        color = black;
        
        for(int y = last[f]; y > ff; y--) {
          matrix.drawPixel(47 - x0, y*2 - 1, color);
        }
      }

      matrix.swapBuffers(false);
  
      last[f] = ff;
    }
  
}

  

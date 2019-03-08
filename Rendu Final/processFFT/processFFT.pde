import ddf.minim.analysis.*;   // minim library is an mp3 reader and analyser for processing
import ddf.minim.*;

import processing.serial.*;   
 
Serial port;          
 
Minim minim;       //initialize minim object
AudioPlayer in;    //initialize the source of the audio player

FFT fft;           //initialize FFT object
float[] peaks;     //array of frequencies

/**
 * Audio vars
 */
int peak_hold_time = 1;  // how long before peak decays
int[] peak_age;  // tracks how long peak has been stable, before decaying

// how wide each 'peak' band is, in fft bins
int binsperband = 10;
int peaksize; // how many individual peak bands we have (dep. binsperband)
float gain = 40; // in dB
float dB_scale = 2.0;  // pixels per dB

int buffer_size = 1024;  // also sets FFT size (frequency resolution)
float sample_rate = 22050;
int spectrum_height = 176; // determines range of dB shown

/**
 * Misc. settings
 */
String serial_port = "COM13";  //set the out port to send data from the FFT (uses Bluetooth port from windows configuration pannel)

int baud_rate = 57600;         //set the serial communication speed rate
boolean enable_32 = true;      //set the display size (default is 32)
int[] freq_range_maxes = { 50, 69, 94, 129, 178, 241, 331, 453, 620, 850, 1241, 1600, 2200, 3000, 4100, 5600 };  

int num_levels = enable_32 ? 32 : 16;  //boolean is true by default (select 16 for smaller display)

int[] freq_array = new int[num_levels]; //actual displayed frequency
int[] last_freq = new int[num_levels];  //array to keep track of the last displayed frequency
float[] freq_height = new float[num_levels];  //avg amplitude of each freq band

int i,g;
float f;

void setup() {
  size(200, 200);     //set the size of the FFT (sample size)
  minim = new Minim(this);  //create minim object
  in = minim.loadFile("centipede.mp3");  //set the minim source from the file (must be an mp3 in the same directory)
  in.loop(); //start reading the file 
  

  port = new Serial(this, serial_port, baud_rate); //set baud rate
  
 
  // create an FFT object that has a time-domain buffer 
  // the same size as line-in's sample buffer
  fft = new FFT(in.bufferSize(), in.sampleRate());
  // Tapered window important for log-domain display
  fft.window(FFT.HAMMING);

  // initialize peak-hold structures
  peaksize = 1+Math.round(fft.specSize()/binsperband);
  peaks = new float[peaksize];
  peak_age = new int[peaksize];
}

void draw() {                                //core method , creating the final dislay   
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
      println(out.trim());    //dislay a real-time rendering on serial 1 (below) 
      port.write(out);        //send data to arduino   
      last_freq[i] = freq_array[i];  //keep last freq in memory (table ) 
      
      if (i % 3 == 0)     //refresh every three freq shown
      delay(3);
    }
  }
  
  delay(2); //delay for and timing
}
 
 
void stop() {
  // always close Minim audio classes when you finish with them
  in.close();
  minim.stop();
  super.stop();
}

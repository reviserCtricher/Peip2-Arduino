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
  //matrix.drawRect(0,0,64 ,32, matrix.Color333(7 ,0 ,0));
 
 
 
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
  
  //matrix.fillRect(0 , 0 , 63 ,31 ,matrix.Color333(0, 0, 0));                           //clear display
  matrix.fillRect(0, 0 , 64 , 32, matrix.Color333(0,0,0)); // Pour les programme II et ultérieurs

// I - Cette version affiche toutes les données sur un écran, sous forme de barres
// dont la hauteur augmente proportionellement par rapport à l'amplitude
 /** 
  for (i = 1; i < 64; i++) {                          // In the current design, 60Hz and noise
    int dat = sqrt(data[i] * data[i] + im[i] * im[i]);   //filter out noise and hum
    matrix.drawLine(i + x, ylim, i + x, ylim - 2*dat, matrix.Color333(0,0,7)); // draw bar graphics for freqs above 500Hz to buffer
    
    
  };   
  
**/

  // II - Affiche le max parmis quatres échantillons, sous forme de cercles dont
  // le rayon augmente en fonction de l'amplitude
/**
  for(int i=0 ; i<4 ; i++){ // Pour chacun des quatres cercles
    for(int j=i*16+1 ; j<i*16+17 ; j++){ // On étudie les valeurs d'un échantillon d'une partie du spectre
      int dat = sqrt(data[j] * data[j] + im[j] * im[j]);
      if(dat>8){ // draw a blue circle then a green one if dat is high enough
        matrix.fillCircle(i*16+7 , 15 , dat/2 , matrix.Color333(0 , 0 ,7)); // dessine un cercle bleu de rayon dat/2 par dessus les précèdents 
        matrix.fillCircle(i*16+7 , 15 , 4 , matrix.Color333(0 , 7 ,7)); // dessine un cercle vert de rayon 4 par dessus le cercle bleu
      }
      else{
        matrix.fillCircle(i*16+7 , 15 , dat/2 , matrix.Color333(0 , 7 ,7)); //dessine un cercle vert de rayon dat/2
      }
    }
  }
  
  **/                                            

  // III - Cette version est une version modifiée de la II, affichée sur deux écrans 
  // Cette version diminue aussi le nombre de dessin demandé à l'écran
/** 
  for(int i=0 ; i<2; i++){
    int maxi=0; // On pose une variable qui stockera la valeur du maximum de l'échantillon
    for(int j=i*16+1 ; j<i*16+17 ; j++){ // On étudie les valeurs d'un échantillon de 16
      int dat = sqrt(data[j] * data[j] + im[j] * im[j]);
      if(dat>maxi){maxi=dat;} //pour chaque valeur de j, on change le maxi si sa val>maxi
    }
     if(maxi>7){ // Si le cercle dépasse le seuil, il est affiché en partie en bleu 
        matrix.fillCircle(i*32+15 , 15 , maxi/2 , matrix.Color333(0 , 0 ,7)); // On dessine le cercle bleu de rayon maxi/2
        matrix.fillCircle(i*32+15 , 15 , 4 , matrix.Color333(0 , 7 ,0)); // On dessine un petit cercle vert par-dessus de rayon 4
      }
      else{ // Si le cercle ne dépasse pas le seuil, on le dessine juste en vert
        matrix.fillCircle(i*32+15 , 15 , maxi/2 , matrix.Color333(0 , 7 ,0));
      }
  }

**/  

  // IV - Cette version est une version modifiée de la deux, avec 8 cercles au lieu
  // de quatres
  for(int i=0 ; i<8; i++){ // On modifie les valeurs prise par i du programme III
    int maxi=0;
    for(int j=i*4+1 ; j<i*4+5 ; j++){ // même chose pour j
      int dat = sqrt(data[j] * data[j] + im[j] * im[j]);
      if(dat>maxi){maxi=dat;}
    }
     if(maxi>7){
        matrix.fillCircle(i*7+8 , (i%2)*12+10 , maxi/5 , matrix.Color333(0 , 0 ,7)); // Le cercle sera affiché dans la moitié
        matrix.fillCircle(i*7+8 , (i%2)*12+10 , 2 , matrix.Color333(0 , 7 ,0)); // supérieure de l'écran une fois sur deux,
      }
      else{
        matrix.fillCircle(i*7+8 , (i%2)*12+10 , maxi/5 , matrix.Color333(0 , 7 ,0)); // sinon il sera affiché dans la moitié inférieure
      }
  }
  
   

};

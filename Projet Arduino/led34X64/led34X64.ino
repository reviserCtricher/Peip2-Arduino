#include <RGBmatrixPanel.h>

#define CLK  11  
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

char Data;
int val=0;

void setup() {
  matrix.begin();
  Serial.begin(9600);
  Serial3.begin(38400);
 
  

}

void loop() {
  if (Serial3.available()){
    Data=Serial3.read();
    
    if (Data=='A') {
    val=Serial3.parseInt();
    Serial.println(val);
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 0, 0));
    matrix.drawCircle(31,15 , val, matrix.Color333(0, 0, 7));
    }
  }


}

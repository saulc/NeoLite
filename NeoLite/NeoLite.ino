



#include "NeoLite.h"
#include "analog.h"
// #include "button.h"
 
int pin = 3, nleds = 46;
 
NeoLite rgb( pin, nleds, 1 ); //pin , # led, color mode

  
int mm = 1; //color mode
int maxbrightness = 255;
volatile bool on = false; 
analog bb(A0, true); //fake analog for brightness fading button.


//void mClick();
////analog mx(A3, true); //2nd pot optional// remove 2 lines
//Button key(3, mClick, true);
//  
//
//void mClick(){
//   if(key.tap() == 0) return;
//    if(mm++ > 9) mm = 0;
//      rgb.setStyle(mm); 
//    
//} 
 
void updateBrightness( ){
    int v = bb.getVal(on ? maxbrightness : 0);
    rgb.setPower(v);
}



void setup() {
  
  //builtin led
//  pinMode(13, OUTPUT );
//  digitalWrite(13, HIGH);
  
//  //'built in pot' 
//  pinMode(15, OUTPUT );
//  digitalWrite(15, LOW);
  
// Serial.begin(115200);
//  Serial.print("--->Acme Leds RGB<---"); 
 
//  pinMode(pin, OUTPUT );
  rgb.ini();
  rgb.tik(); 
  on = true;
//  key.ini(); //ini button
}

 int k  = 0;
 int l = 2;
 
void loop() {  
  if(k++ > 100000){
    k=0;
//    if(l++ > 5)
//      l = 1;
    if(k ==0){
      updateBrightness();

    }
    int t = rgb.tik();
    
//  Serial.print("t : "); 
//  Serial.println(l); 
  }
} 
  

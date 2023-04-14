



#include "NeoLite.h"
#include "analog.h"
 #include "button.h"
 
int pin = PIN_NEOPIXEL, nleds = 2;
 
NeoLite rgb( pin, nleds, 0 ); //pin , # led, color mode

  
volatile int mm = 1; //color mode
int maxbrightness = 255;
volatile bool mOn = false; 
analog bb(A0, true); //fake analog for brightness fading button.


void mClick();
//analog mx(A3, true); //2nd pot optional// remove 2 lines
Button key(0, true);
  

void mClick(){
  int tt = key.tap();
   if( tt== 0) return;
   if(tt = 1){
    if(mm++ > 9) mm = 0;
//      rgb.setStyle(mm); 
//   }
//   else if(tt == 2){
//    mm--;
     mOn = !mOn;
   }
    
} 
 
void setup() {
  
  //builtin rgb power pin
  pinMode(38, OUTPUT );
  digitalWrite(38, HIGH);
//  delay(11);
  
//  //'built in pot' 
//  pinMode(15, OUTPUT );
//  digitalWrite(15, LOW);
  
// Serial.begin(115200);
//  Serial.print("--->Acme Leds RGB<---"); 
 
//  pinMode(pin, OUTPUT );
  rgb.ini();
  rgb.tik(); 
  mOn = true;
  key.ini(); //ini button
  attachInterrupt(0, mClick, FALLING );  
}
 
    int t = 0;
 int l = 2;

 int f = 0;
 bool pp = false;
 
void updateBrightness( ){
    int v = bb.getVal(mOn ? maxbrightness : 0);
    rgb.setPower(v);
//    
//  Serial.print(pp);
//  Serial.print("  ");
//  Serial.print(mOn);
//  Serial.print("   color : "); 
//  Serial.print(mm); 
//  Serial.print("  v : "); 
//  Serial.println(v); 
}



void loop() {  
//  if(t > 1000){
//    k=0;
//    if(l++ > 5)
//      l = 1;
    if(t != l){
//      if(f++ > 1000){
//        f = 0;
//        pp = !pp;
//  digitalWrite(NEOPIXEL_POWER, pp);
      }
      
      updateBrightness();
      l = t;
    }
     t = rgb.tik();
    
//  Serial.print("t : "); 
//  Serial.println(t); 
  
} 
  

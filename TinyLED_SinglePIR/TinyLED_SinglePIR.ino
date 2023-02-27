



#include "PinChangeInterrupt.h"
#include "analog.h"
 #include "button.h"
  
/* 
 * tiny + tip120 12v buck output.
 *          pir motion detector servo pinout.
 *          
 */

//void aClick();                   
//Button key(2, aClick, true); // 2. altmode aclick // switch mode mclick
   
short maxbrightness = 255; 
volatile short mb = 0;
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
                                          
analog aa(A3); //a3  p3 . a2 p4.  a1 p2  brightness input pot

int ledPin = 0;
short sensorpin = 2; 
volatile long lastTrigger = 0;
   
void checkMax(){ 
   maxbrightness = map(aa.getVal() , 0, 255, 10, 255);
}

void updateFade(){ 
   mb = bb.getVal( on==true ? maxbrightness: 0); 
   analogWrite(ledPin, mb );
//   analogWrite(4, mb );
}
  

void motion(){ 
  
      lastTrigger = micros(); 
    if(on){
       
    }else {
       on = true;
       
    }
}

void tic(){
  
  if(on and micros()-lastTrigger > 40000000){
    on = false;
    lastTrigger = 0;
  }
}

void setup() {

  
//  pinMode(4, OUTPUT ); 
//   analogWrite(4, 0 );
   
  pinMode(ledPin, OUTPUT ); 
   analogWrite(ledPin, 0 );
  
  pinMode(sensorpin, INPUT);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt( sensorpin), motion , RISING);

      lastTrigger = micros(); 
      //on at power up
      
} //end setup

 int k  = 0 ;
 
void loop() {  
  tic();
  
      if(k ==0) checkMax();
      if(k  ==1) updateFade(); 
    if(k++ > 3000)   k = 0;  
     
     
} //end loop
  





#include "PinChangeInterrupt.h"
#include "NeoLite.h"
#include "analog.h" 
 
short mpin = 0, nleds = 64;
 
NeoLite rgb( mpin, nleds, 0 ); //pin , # led, color mode

/* 
 * alt mode mx key + pot 
 *          button test motion action
 *          double tap  
 *          pot color mode
 *          pir motion detector servo pinout.
 *          
 */
 
  
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 0; //switch mode
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
// analog aa(A2, true);

short sensorpin = 1; 
 
volatile long lastTrigger = 0;
  
void updateMode(){  
    //sending fake 'analog' values directy for fade
     int b = bb.getVal( on==true ? maxbrightness: 0); 
     rgb.setPower(b); 
}

void checkMode(){
  //  mm = map(aa.getVal(), 0, 255, 0, 10);
   rgb.setStyle(mm);
}
  

void motion(){ 
  
      lastTrigger = micros(); 
    if(on){
       
    }else {
       on = true;

    }
}

void checkMotion(){
  if(!on) return;
  long tl = micros()-lastTrigger;
  long l = round(tl/2000000);
  if(on and tl > 24000000){
    on = false;
    lastTrigger = 0; 
    rgb.toc(0);
    // checkMode();
  }
  else if(on and l > 0) rgb.toc(l);
}

void setup() {

  
  pinMode(0, OUTPUT );
  rgb.ini();
  rgb.tik();
   
  
  pinMode(sensorpin, INPUT);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt( sensorpin), motion , RISING);

      lastTrigger = micros(); 
} //end setup

 int k  = 0;
 
void loop() {  
  checkMotion();
  
    if(k  ==0) updateMode();
    // if(k% 1000==0 ) checkMode();
    
    k = rgb.tik();
    // delay(11);
     
} //end loop
  

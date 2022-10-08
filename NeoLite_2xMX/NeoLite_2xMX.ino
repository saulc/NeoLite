



#include "NeoLite.h"
#include "analog.h"
 #include "button.h"
 
short mpin = 6, nleds = 46;
 
NeoLite rgb( mpin, nleds, 0 ); //pin , # led, color mode

/*
 * nano + 2x MX keys
 *          
 */
void aClick();
void bClick();
int pba = 2, pbb = 3; 
Button keya(pba , aClick,true); 
Button keyb(pbb , bClick, true); 
 
volatile short cm = 0; //color mode
volatile short bm = 4; // 0-4 brightness steps
short maxbrightness = 255; 
volatile bool lon = true; 
volatile bool bmode = false; 
analog bb(A0, true); //fake analog for brightness fading button.

void aClick(){
  int t = keya.tap();
   if(t == 0) return;
   else if(t == 2) {
    lon = !lon;
   }else 
   if(bmode){ 
      if(bm++>4) bm = 0;
    } else{
      if(cm++>10) cm = 0;
       rgb.setStyle(cm);
    }
    
   
}

void bClick(){
  int t = keyb.tap();
   if(t == 0) return; 
   else if(t == 2) {
    bmode = !bmode;
   }
   else if(bmode){  
      if(bm--<0) bm = 4;
    } else{
      if(cm--<0) cm = 9;
       rgb.setStyle(cm);
    }
    
}

int getBr(){
  switch(bm){
    case 0: return 11;
    case 1: return 33;
    case 2: return 88;
    case 3: return 151;
    case 4: return 255;
  }
  return 111;
}

void updateMode(){   
    maxbrightness = getBr();
    //sending fake 'analog' values directy for fade
     int b = bb.getVal( lon==true ? maxbrightness: 0); 
     rgb.setPower(b); 
}

void setup() {

 
  pinMode(mpin, OUTPUT );
  rgb.ini();
  rgb.tik(); 
  keya.ini();
  keyb.ini();

} //end setup

 int k  = 0;
 
void loop() {  

    if(k  ==0) updateMode();
    k = rgb.tik();
     
} //end loop
  

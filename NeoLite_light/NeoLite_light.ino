 



#include "NeoLite.h"
#include "analog.h"
 
short mpin = 0, nleds = 64;
 
NeoLite rgb( mpin, nleds, 1 ); //pin , # led, color mode

/*
 * tiny rgb - photo resistor
 * 
 *    
 */
//mode pot 
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 0; //switch mode
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
analog li(A3, true);  
analog aa(A1, false);  //p2A1 p3A3 p4A2

  
short shigh = 1;
short soff =  4;

//2 position spdt switch
void checkSwitch(){
  bool h = digitalRead(shigh);
  bool o = digitalRead(soff);
 //wtf this is so picky idk why. spdt 
  if(h == LOW) vv = 2;
   else if(o == HIGH and h == HIGH)  vv = 1;
   else {
       vv = 0;
//       on = false;
       return;
   }
//    on = true;
}

void updateBrightness(){
    int sr = li.getVal();
    if(vv == 0) on = sr < 111;
    else if(vv == 2)  on = sr >= 111;
    else on = true;
    
//      //brightness mode
//     maxbrightness = getSwitchVal(); 
     int b = bb.getVal( on==true ? maxbrightness: 0); 
     rgb.setPower(b);
}
  
void updateMode(){ 
      //color mode
      mm = map(aa.getVal(), 0, 255, -1, 10);
      rgb.setStyle( mm <1 ? 0 : mm);

}

void setup() {

  
  pinMode(shigh, INPUT_PULLUP );
  pinMode(soff, INPUT_PULLUP );
  
  rgb.ini();
  rgb.tik(); 
 
  for(int i=0; i<22; i++) updateMode();
} //end setup

 int k  = 0;
 
void loop() {  

    if(k  ==0) {
      updateBrightness(); 
      updateMode(); 
    checkSwitch();
    } 
//    
//    if(k% 1000==0) 
    k = rgb.tik();
     
} //end loop
  

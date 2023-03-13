 



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
analog li(A2, true);  
analog aa(A1, true);  

void updateBrightness(){
    int sr = li.getVal();
    on = sr < 111;
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

  
  rgb.ini();
  rgb.tik(); 
 
  for(int i=0; i<22; i++) updateMode();
} //end setup

 int k  = 0;
 
void loop() {  

    if(k  ==0) {
      updateBrightness(); 
      updateMode();
    } 
    
    k = rgb.tik();
     
} //end loop
  

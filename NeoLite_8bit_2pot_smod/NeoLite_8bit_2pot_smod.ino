



#include "NeoLite.h"
#include "analog.h"
 #include "button.h"
 
short mpin = 6, nleds = 46;
 
NeoLite rgb( mpin, nleds, 0 ); //pin , # led, color mode

/*
 * tiny rgb mx key + switch off/low/high 
 * alt mode mx key + pot 
 *          button color mode 
 *          double tap on/off
 *          pot brightness
 *          
 */

//tiny 1/4 a3
//switch pins digital in
short shigh = 12;  //broken 2 pos switch. down = button
short soff =  13;
void aClick();  
analog aa(A1); 
Button key(shigh, aClick, false); // 2. altmode aclick // switch mode mclick
 

//mode pot
analog ab(A2 , true); //2nd param flip analog direction
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 0; //switch mode
volatile bool on = true; 
volatile bool full = false; 
analog bb(A0, true); //fake analog for brightness fading button.



//2 position spdt switch
void checkSwitch(){
  bool h = digitalRead(shigh);
  bool o = digitalRead(soff);
 //wtf this is so picky idk why. spdt 
  if(h == LOW) vv = 2;
   else if(o == HIGH and h == HIGH)  vv = 1;
   else {
       vv = 0;
       on = false;
       return;
   }
    on = true;
}


//off low full
int getSwitchVal(){
  if(vv == 0) return 0;  // 3 mode
  else return (vv == 1 ? 111: 255);
}

void updateMode(){  
    int t = aa.getVal();
    if(full) maxbrightness = 255;
    else maxbrightness = t < 22 ? 22: t;  
    
    //sending fake 'analog' values directy for fade
     int b = bb.getVal( on==true ? maxbrightness: 0); 
     rgb.setPower(b); 
}
 
void aClick(){
  int t = key.tap();
   if(t == 0) return;
    full = !full;
}


void setup() {

 
  pinMode(mpin, OUTPUT );
  rgb.ini();
  rgb.tik();
  pinMode(shigh, INPUT_PULLUP );
  pinMode(soff, INPUT_PULLUP );
  key.ini();

} //end setup

 int k  = 0;
 
void loop() {  

    if(k  ==0) updateMode();
    if(k% 1000==0) checkSwitch();
    
    k = rgb.tik();
     
} //end loop
  

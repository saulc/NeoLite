 



#include "NeoLite.h"
#include "analog.h"
 #include "button.h"
 
short mpin = 5, nleds = 121;
 
NeoLite rgb( mpin, nleds, 1 ); //pin , # led, color mode

/*
 * tiny rgb multimode pot control
 *    switch off/ change brightness/ change color mode
 *    
 */
 
//nano table 2/6 high/low a2 mode
//tiny 1/4 a3
//switch pins digital in
short shigh = 14;
short soff =  15;
//short shigh = 2;
//short soff =  3;

//mode pot 
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 0; //switch mode
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
analog aa(A1, false); //color mode//2nd pot optional// remove 2 lines

//analog br(A1, false); //fake analog for brightness fading button.
//void mClick();
//Button key(2, mClick, true);

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

int bri(){ 
  return 111;
//  return map(br.getVal(), 0, 255, 1, 222);
//  int b =  br.getVal();
//  int t = 0;
//  int s = 240;
//  if(b < s){
//    t = map(b, 0, s-1, 11, 211);
//  }else{
//    t = map(b, s, 255, 200, 222);
//  }
//  return t;
}

//off low full
int getSwitchVal(){
  if(vv == 0) return 0;  // 3 mode
  else return (vv == 1 ? bri() : 255);
}

void updateBrightness(){
//      //brightness mode
     maxbrightness = getSwitchVal(); 
     int b = bb.getVal( on==true ? maxbrightness: 0); 
     rgb.setPower(b);
}

void updateMode(){ 
      //color mode
      mm = map(aa.getVal(), 0, 255, 1, 10);
      rgb.setStyle(  mm);
     
}

//void mClick(){
//   if(key.tap() == 0) return;
//    if(mm++ > 9) mm = 0;
//      rgb.setStyle(mm); 
//    
//}



void setup() {

 
//  pinMode(0, OUTPUT );
  rgb.ini();
  rgb.tik();
  pinMode(shigh, INPUT_PULLUP );
  pinMode(soff, INPUT_PULLUP );
//  key.ini();

  for(int i=0; i<22; i++) updateMode();
} //end setup

 int k  = 0;
 
void loop() {  

    if(k  ==0) {
      updateBrightness();
      updateMode();
    }
    if(k% 1000==0)  checkSwitch();
    
    k = rgb.tik();
     
} //end loop
  

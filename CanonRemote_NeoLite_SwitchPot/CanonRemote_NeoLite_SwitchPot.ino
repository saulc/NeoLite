



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
short camShutter = 15;
short camFocus =  14;
//short shigh = 2;
//short soff =  3;

//mode pot
//analog ab(A3 , true); //2nd param flip analog direction
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 0; //switch mode
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
analog aa(A0, false); //color mode//2nd pot optional// remove 2 lines

//void mClick();
//Button key(2, mClick, true);

//2 position spdt switch
//void checkSwitch(){
//  bool h = digitalRead(shigh);
//  bool o = digitalRead(soff);
// //wtf this is so picky idk why. spdt 
//  if(h == LOW) vv = 2;
//   else if(o == HIGH and h == HIGH)  vv = 1;
//   else {
//       vv = 0;
////       on = false;
//       return;
//   }
////    on = true;
//}


//off low full
int getSwitchVal(){
  if(vv == 0) return 0;  // 3 mode
  else return (vv == 1 ? 111: 255);
}

void updateBrightness(){
//      //brightness mode
     maxbrightness = getSwitchVal(); 
     int b = bb.getVal( on==true ? maxbrightness: 0); 
     rgb.setPower(b);
}

void updateMode(){ 
      //color mode
      mm = map(aa.getVal(), 0, 255, -1, 9);
      rgb.setStyle( mm <1 ? 0 : mm);
     
}

//void mClick(){
//   if(key.tap() == 0) return;
//    if(mm++ > 9) mm = 0;
//      rgb.setStyle(mm); 
//    
//}

bool cf = false;
bool cs = false;
 int k  = 0;

void focus(int t){
  static int fs = k+t; 
  cf = true;
  if(k > fs) cf = false;
  digitalWrite(camFocus, (cf== true ? LOW: HIGH) );
}

void cap(int t){
  
  static int ss = k+t;
  cs = true;
  if(k > ss) cs = false;
  digitalWrite(camShutter, (cs== true ? LOW: HIGH) ); 
  
}



void setup() {

  Serial.begin(57600);
  
      Serial.print("acme cam remote timer: ");
  pinMode(camFocus, OUTPUT );
  pinMode(camShutter, OUTPUT );
  
  digitalWrite(camFocus, HIGH );
  digitalWrite(camShutter, HIGH );
 
//  pinMode(0, OUTPUT );
  rgb.ini();
  rgb.tik();
//  pinMode(shigh, INPUT_PULLUP );
//  pinMode(soff, INPUT_PULLUP );
//  key.ini();

  for(int i=0; i<22; i++) updateMode();
} //end setup

 int l = 0;
 
void loop() {  

    if(k%1000  ==0) {
      if(l++ > 11) l =0;
      Serial.print("Focus: ");
      Serial.print(cf);
      Serial.print(" Shutter: ");
      Serial.println(cs);
      updateBrightness();
      updateMode();
    }
//    if(k% 1000==0)  checkSwitch();
    if(l == 1) cap(2111);
    if(l >= 7) focus(2111);
    
    k = rgb.tik();
     
} //end loop
  

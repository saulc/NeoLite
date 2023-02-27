



#include "NeoLite.h"
#include "analog.h"
 #include "pbutton.h"
 
short mpin = 3, nleds = 18;
 
NeoLite rgb( mpin, nleds, 1 ); //pin , # led, color mode
  

//mode pot
//analog ab(A3 , true); //2nd param flip analog direction
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 0; //switch mode
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
//analog aa(A0, false); //color mode//2nd pot optional// remove 2 lines

analog bl(A0); 
analog right(A0);   
analog left(A0);  

int leds[] = {5, 9, 10};
 
 
pbutton bt(21);
 

void updateBrightness(){
//      //brightness mode 
     int b = bb.getVal( on==true ? maxbrightness: 0); 
     rgb.setPower(b);
}
 
void mClick(){
//   if(key.tap() == 0) return;
    if(mm++ > 9) mm = 0;
      rgb.setStyle(mm); 
    
} 

bool l0 = true, l1 = true, l2 = true;
bool checkBtn(int lp){
  int v = bt.getVal();
//  Serial.print("V: ");
//  Serial.println(v);
  on = (v > 3);
  switch(v){
    case 0: l0 = false; l1 = false; l2 = false; break;
    case 1: l0 = true;  l1 = false; l2 = false; break;
    case 2: l0 = false;  l1 = true; l2 = true; break;
    case 3: l0 = true;  l1 = true; l2 = false; break;
    case 4: l0 = true;  l1 = true; l2 = true; break;
  } 
  if(v == 3){
    l1 = lp > 30;
    l2 = lp < 70;
//  Serial.print(lp);
//  Serial.print(" a: ");
//  Serial.print(l1);
//  Serial.print(" b: ");
//  Serial.println(l2);
  }
  else if(v == 4){
    l1 = lp > 10;
    l2 = lp < 90;
  }
  fade(lp, v);
}


void fade(int lp, int mode){
  for(int i=0; i<3; i++) set(i, lp);
}

void set(int p, int mode){
//      //brightness mode 
  int b = 0;
    switch(p){
      case 0: 
     b = bl.getVal( l0==true ? maxbrightness: 0); break;
      case 1: 
     b = right.getVal( l1==true ? maxbrightness: 0);  break;
      case 2: 
     b = left.getVal( l2==true ? maxbrightness: 0); break;
    }
     analogWrite(leds[p], b);
}

 
void setup() { 
  
  Serial.begin(9600);
  for(int i=0; i<11; i++) on = bt.getVal();
  rgb.ini();
  rgb.tik(); 
//  key.ini();
  for(int i=0; i<3; i++)
  pinMode(leds[i], OUTPUT); 
  
  pinMode(17, OUTPUT); 
  pinMode(30, OUTPUT); 
  digitalWrite(17, LOW);
  digitalWrite(30, LOW);
}

 int l = -1;
 
void loop(){  
    int k = rgb.tik(); 
    if(k == 0) {
      checkBtn(l);
      if(l++ > 100) l = 0;
      if(l%3 ==0) 
      updateBrightness(); 
    }
    
//    if(l<3 and l >= 0)     set(l);
} //end loop


  

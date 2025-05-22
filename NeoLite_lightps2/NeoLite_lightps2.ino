 



#include "NeoLite.h"
#include "analog.h"
 
short mpin = 5, nleds = 64;
 
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
analog bb(A1, true); //fake analog for brightness fading button.
analog li(A3, true);  
analog aa(A0, false);  //p2A1 p3A3 p4A2

  
int cut = 55;
short shigh = 15;
short soff =  14;

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
  // Serial.println(sr);
    if(vv == 0) on = sr < cut;
    else if(vv == 2)  on = sr >= cut;
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

  // Serial.begin(115200);


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH );
  pinMode(17, OUTPUT );
  digitalWrite(17, HIGH );
  pinMode(30, OUTPUT );
  digitalWrite(30, HIGH );
  pinMode(shigh, INPUT_PULLUP );
  pinMode(soff, INPUT_PULLUP );
  
  rgb.ini();
  rgb.tik(); 
 
  for(int i=0; i<22; i++) updateMode();
} //end setup

 int k  = 0;
 
void loop() {  

    if(k == 0) {
      
      updateBrightness(); 
      updateMode(); 
      checkSwitch();

    } 
//    
  //  if(k% 1000==0) 
    k = rgb.tik();
     
} //end loop
  

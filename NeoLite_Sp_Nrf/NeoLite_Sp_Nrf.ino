 


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 (CE & CS)
RF24 radio(8, 9);
// for nano tx remote
//RF24 radio( 10, 9);

// sets the role 1 rx, 2 tx
const int role_remote = 1;
const int role_led = 2;

const int role =   role_remote; //role_led; //role_remote; //

// Pins on the remote for buttons
const uint8_t num_buttons = 4;

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Remote", "LED Board"};

//
// Payload
//

int button_states[num_buttons];

const uint8_t msgSize = sizeof(button_states);

int timeOut = 1000;
long last = 0;


#include "NeoLite.h"
#include "analog.h"
 #include "button.h"
 
short mpin = 5, nleds = 12;
 
NeoLite rgb( mpin, nleds, 1 ); //pin , # led, color mode

/*
 * tiny rgb multimode pot control
 *    switch off/ change brightness/ change color mode
 *    
 */
 
//nano table 2/6 high/low a2 mode
//tiny 1/4 a3
//switch pins digital in
short shigh = 4;
short soff =  20;
//short shigh = 2;
//short soff =  3;

//mode pot 
short mm = 0; //color mode
short maxbrightness = 255;
volatile short vv = 2; //switch mode
volatile bool on = true; 
analog bb(A0, true); //fake analog for brightness fading button.
analog aa(A0, true); //color mode//2nd pot optional// remove 2 lines


analog br(A1, true); //fake analog for brightness fading button.
//void mClick();


//Button key(2, mClick, true);

/**************************
************************/



void off(){
  mm = 0;
  on = false;
}

void checkSoff(){ 
  bool o = digitalRead(soff); 
   if(o == LOW) off();
   else on = true;
}
 

int updateBrightness(){ 
      maxbrightness = br.getVal();
     int b = bb.getVal( on==true ? maxbrightness: 10); 
     rgb.setPower(b);
     return b;
}

void updateMode(){ 
      //color mode
      //detect a mode change, trigger an update to be sent out
      //then return to ledmode.
      if(!on) return;
      
      mm = map(aa.getVal(), 0, 255, 1, 9);
      rgb.setStyle(  mm);
     
}


void remoteUpdate(int a, int b, int c, int d){
    mm = c;
    on = (d == 1);
    if(on) rgb.setStyle(mm);  
    else{
    rgb.setStyle(mm = 0); 
    }
     maxbrightness = b;  
}

//void mClick(){
//   if(key.tap() == 0) return;
//    if(mm++ > 9) mm = 0;
//      rgb.setStyle(mm); 
//    
//}



void setup() {

  Serial.begin(57600);
  Serial.println("Acme RGB TEST");
  printf_begin();
  for(int i=0; i<11; i++) if(Serial) break;
  printf("Acme RGB");
  printf("\n\rRF24/examples/led_remote/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);    //RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setDataRate(RF24_250KBPS);
   //speed  RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens a single pipes for these two nodes to communicate
  // back and forth.  One listens on it, the other talks to it.

  if ( role == role_remote )
  {
    radio.openWritingPipe(pipe);
  }
  else
  {
    radio.openReadingPipe(1,pipe);
  }

  //
  // Start listening
  //

  if ( role == role_led )
    radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
  delay(111);


 
//  pinMode(0, OUTPUT );
  rgb.ini();
  rgb.tik();
//  pinMode(shigh, INPUT_PULLUP );
  pinMode(soff, INPUT_PULLUP );
//  key.ini();
  if(role != role_led)
  for(int i=0; i<22; i++) updateMode();
} //end setup

void rdio(){
  
  //neutral both channels for no data for a second
  long now = millis() - last;
  if(now >= timeOut){
            printf("Timed out: %d \n\r", now);
     last = millis();
  }
  
  if ( role == role_led )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      while (radio.available())
      {
        // Fetch the payload, and see if this was the last one.
        radio.read( button_states, msgSize );

          int a = button_states[0];
          int b = button_states[1];
          int c = button_states[2];
          int d = button_states[3]; 
          
        remoteUpdate(a, b, c, d);
 
        // Spew it
        if(button_states)
               printf("Got buttons \n\r");
          else   printf("Got nunnn ..\n\r");


          
        for(uint8_t i=0; i<num_buttons; i++) {
             
               printf("%d == ", button_states[i]);
               
          
        }
      
      
      last = millis();
      
      }
    } 
  }
}

void remote(int bri){
  

  if ( role == role_remote )
  {
    
    button_states[0] = 0; //channel/group id?
    button_states[1] = maxbrightness;  //current max brightness
    button_states[2] = mm;  //color mode
    button_states[3] = (on ? 1: 0); //idk?
 
    
      printf("Now sending...%d %d %d %d ", button_states[0], button_states[1], button_states[2], button_states[3]);
      bool ok = radio.write( button_states, msgSize );
      if (ok)
        printf("ok\n\r");
      else
        printf("failed\n\r");


  }
}

 int k  = 0;
 
void loop() {  

    if(k  ==0) {
       int b = updateBrightness();
      if(role == role_led) rdio();
      else {
      updateMode();
      remote(b);
      } 
    }
    if(k% 10000==0)   checkSoff();
    
    k = rgb.tik();
     
} //end loop
  

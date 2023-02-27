


#ifndef pbutton_h
#define pbutton_h

#include "Arduino.h"
/*
 * Saul Castro
 * 
 * analog smoothing
 * 
  */

class pbutton{

    public:
    pbutton(int p){ pin = p; flip = false; } 
    
    int getVal( ){   
      
        int a = pulseIn(pin, HIGH);
//        if(flipa)   a = map(a, 0, 1023, 0, 255 ); 

        bool b = (getVal(a) < 1555);
        if( b != flip){
//          hit();
        if(mod++ >= modes) mod = 0;
          flip = b;
        }
        return mod;
    }

    int hit(){
        if(mod++ >= modes) mod = 0;
        return mod;
    }
    int getVal(int a){
        total = total - readings[readIndex];
      
        // read from the sensor:
        readings[readIndex] = a;
        // add the reading to the total:
        total = total + readings[readIndex];
        // advance to the next position in the array:
        readIndex = readIndex + 1;
      
        // if we're at the end of the array...
        if (readIndex >= numReadings) {
          // ...wrap around to the beginning:
          readIndex = 0;
        }
      
        // calculate the average:
        average = total / numReadings;
  
       return average; }

   private:

    bool flip; //flipped the latching pwm switch
    int mod = 0;
    static const int modes = 4;
   //analog smoothing 
    int pin;
    static const int numReadings = 11;    //more readings for a slower fade.
    int readings[numReadings];      // the readings from the analog input
    int readIndex = 0;              // the index of the current reading
    int total = 0;                  // the running total
    int average = 0;                // the average

  };


  #endif

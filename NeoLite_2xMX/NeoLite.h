
#ifndef NEOLITE_h
#define NEOLITE_h 

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif



class NeoLite{
    public:
      NeoLite(int pwm, int numberofleds){
        pin = pwm;
        leds = numberofleds; 
      }
      
      NeoLite(int pwm, int numberofleds, int controlMode  ){
        cMode =  controlMode;
        pin = pwm;
        leds = numberofleds;  
      }
      ~NeoLite(){}

      void ini( ){
          lites = Adafruit_NeoPixel(leds, pin, NEO_GRB + NEO_KHZ800); 
        lites.begin();
        lites.setBrightness(0);  //remove flash on power
        lites.show(); // Initialize all pixels to 'off'
      }


      void color(int r, int g, int b){
        setColor(r, g, b);
         
      }
      void setStyle(int c){ 
            cMode = c; 
              if(c > nModes) cMode = nModes;
              else if(c < 0) cMode = 0;
        }
        
      void setMode( ){
        switch(cMode){ 
//          case 0:  color(100, 0, 0); break;
      
          case 0: //red
                color(255, 0, 0 ); break;
          
          case 1:  color(255, 0, 70 ); //pink
                   break;
            
          case 2: //purpleish..
                 color(105, 0, 255 ); break;
          
          case 3: color(77, 88, 0 ); break; //yellow
          
          case 4: ///greenblue
                color(0, 255, 10 ); break;
                
          case 5: //blue/green
                color(0, 188, 30 ); break;
          
          case 6: //blue
                color(0, 111, 255 ); break;
          
          case 7: //white?
                color(255, 200, 250 ); break;
          
          case 8:  rcy( );// delay(55);
                  break;
         
          case 9: rainbo( ); //delay(55); 
                  break; //no break for dual mode
                  
          default: color(111, 0, 0); break;
        }
      }
        
        
        //timer updated rainbow 
        void rainbo( ) {
          if(j++ > 255) j = 0;
          uint16_t i;
            for(i=0; i<lites.numPixels(); i++) {
              lites.setPixelColor(i, Wheel((i+j) & 255));
            }
            lites.show();
           
          
        }
        // Slightly different, this makes the rainbow equally distributed throughout
        void rcy( ) {
          uint16_t i;
          if(j++ > 255) j = 0;
             for(i=0; i< lites.numPixels(); i++) {
              lites.setPixelColor(i, Wheel(((i * 256 / lites.numPixels()) + j) & 255));
            }
            lites.show(); 
          
        }
        
        
        
        // Fill the dots one after the other with a color
        void colorWipe(uint32_t c, uint8_t wait) {
          for(uint16_t i=0; i<lites.numPixels(); i++) {
            lites.setPixelColor(i, c);
            lites.show();
            delay(wait);
          }
        }
        
        void rainbow(uint8_t wait) {
          uint16_t i, j;
        
          for(j=0; j<256; j++) {
            for(i=0; i<lites.numPixels(); i++) {
              lites.setPixelColor(i, Wheel((i+j) & 255));
            }
            lites.show();
            delay(wait);
          }
        }
        
        // Slightly different, this makes the rainbow equally distributed throughout
        void rainbowCycle(uint8_t wait) {
          uint16_t i, j;
        
          for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
            for(i=0; i< lites.numPixels(); i++) {
              lites.setPixelColor(i, Wheel(((i * 256 / lites.numPixels()) + j) & 255));
            }
            lites.show();
            delay(wait);
          }
        }
        
        //Theatre-style crawling lights.
        void theaterChase(uint32_t c, uint8_t wait) {
          for (int j=0; j<10; j++) {  //do 10 cycles of chasing
            for (int q=0; q < 3; q++) {
              for (int i=0; i < lites.numPixels(); i=i+3) {
                lites.setPixelColor(i+q, c);    //turn every third pixel on
              }
              lites.show();
        
              delay(wait);
        
              for (int i=0; i < lites.numPixels(); i=i+3) {
                lites.setPixelColor(i+q, 0);        //turn every third pixel off
              }
            }
          }
        }
        
        //Theatre-style crawling lights with rainbow effect
        void theaterChaseRainbow(uint8_t wait) {
          for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
            for (int q=0; q < 3; q++) {
              for (int i=0; i < lites.numPixels(); i=i+3) {
                lites.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
              }
              lites.show();
        
              delay(wait);
        
              for (int i=0; i < lites.numPixels(); i=i+3) {
                lites.setPixelColor(i+q, 0);        //turn every third pixel off
              }
            }
          }
        }
        
        // Input a value 0 to 255 to get a color value.
        // The colours are a transition r - g - b - back to r.
        uint32_t Wheel(byte WheelPos) {
          WheelPos = 255 - WheelPos;
          if(WheelPos < 85) {
            return lites.Color(255 - WheelPos * 3, 0, WheelPos * 3);
          }
          if(WheelPos < 170) {
            WheelPos -= 85;
            return lites.Color(0, WheelPos * 3, 255 - WheelPos * 3);
          }
          WheelPos -= 170;
          return lites.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }

        void setColor(int r, int g, int b) {
          
              lites.setPixelColor(0, lites.Color(r, g, b) );
              if(leds > 1){
                 uint16_t mid = leds/2;
                 uint16_t i = mm%mid;   
              //      lites.setPixelColor(lites.numPixels()-i, c);
                    lites.setPixelColor(mid+i, lites.Color(r, g, b));
                    lites.setPixelColor(mid-i, lites.Color(r, g, b));
              }
              lites.show();
           
        }
        
        int getModeCount(){
          return nModes;
        }
        void setPower(int p){
          if(p > maxbrightness) p = maxbrightness;
          
          br = p;
          lites.setBrightness(br);
        } 
      
        int tik(){
            if(mtime++ > 10000) mtime = 0; //a fake timer for attiny85
            if(mtime == 0) {
            if(mm++ > 1000) mm = 0;  //needs adjustment for 32bit //esp32/rp2040
            setMode(); // make changes bit/by bit/ 
            }
            return mtime;
        }
    private:

      int maxbrightness = 255;
      int br = 50;  //brightness
   
      int mtime = 0;    //cpu time
      int mm = 0;     //animation time
      uint16_t  j = 0;  // rainbow animation index
      int cMode = 0;
      const int nModes = 9;
      
    int pin = 5;
    int leds = 11; //how many LEDS in the strip
    
    Adafruit_NeoPixel lites ; 
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
};


#endif

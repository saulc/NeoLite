// Placed in the public domain by Earle F. Philhower, III, 2022

#include <WiFi.h> 

#ifndef STASSID
#define STASSID "HOME"
#define STAPSK "castrowifi"
#endif

#include "NeoLite.h"
#include "analog.h"
 
int pin = 3, nleds = 120;
 
NeoLite rgb( pin, nleds, 1 ); //pin , # led, color mode
  
int mm = 0; //color mode
int maxbrightness = 255;
volatile bool on = false; 
analog bb(A0, true); //fake analog for brightness fading button.
//rgb

const char* ssid = STASSID;
const char* password = STAPSK;

int port = 8080;

int pins[] = {12, 11, 10, 9, 8};
int dat[5]; 

WiFiServer server(port);

void setup() {
//  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname("PicoW2");
  Serial.printf("Connecting to '%s' with '%s'\n", ssid, password);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print(".");
    delay(100);
  }
//  Serial.printf("\nConnected to WiFi\n\nConnect to server at %s:%d\n", WiFi.localIP().toString().c_str(), port);

  server.begin(); 

  rgb.ini();
  rgb.tik(); 
  on = true;
}  
void process(String dat){
//  Serial.print("Input: ");
//  Serial.println( dat);
  char in[] = {'a', 'b', 'c', 'd', 'e', 'f'};
   for(int i=0;i<5; i++){
    int st = dat.indexOf(in[i]);
    int en = dat.indexOf(in[i+1]);
      String v = dat.substring(st+1, en); 
      int vi = v.toInt();
//  Serial.print(i);
//  Serial.print(" : ");
//  Serial.println( vi);
      dat[i] = vi;
  }
      mm = dat[0];
      maxbrightness = dat[1];
      rgb.setStyle(mm); 
}
 
void updateBrightness( ){
    int v = bb.getVal(on ? maxbrightness : 0);
    rgb.setPower(v);
}


 int k  = 0;
 int l = 2;
void loop() {
  if(k++ > 10000){
    k=0;
//    if(l++ > 5)
//      l = 1;
  }
    if(k ==0){
      updateBrightness();

    }
    int t = rgb.tik();

    
  static int i;
//  delay(1000);
//  Serial.printf("--loop %d\n", ++i);
//  delay(10);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  client.println("Type anything and hit return");
  while (!client.available()) {
    delay(10);
  }
  String req = client.readStringUntil('\n');
  process(req);
//  Serial.println(req);
  client.printf("Hello from Pico-W\r\n");
  client.flush();
}

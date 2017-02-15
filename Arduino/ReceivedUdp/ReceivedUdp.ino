
#include <ESP8266WiFi.h>
#include "FastLED.h"
#include <WiFiUdp.h>

#define NUM_LEDS 100
#define DATA_PIN 14

// Define the array of leds
CRGB leds[NUM_LEDS];

const char* ssid     = "TP-LINK_54F0";
const char* password = "94124057";
unsigned int port = 2390;
WiFiUDP Udp;

char packetBuffer[512];
char ReplyBuffer[] = "acknowledged";

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

   Udp.begin(port);
}

int value = 0;

void loop() 
{    
    int packetSize = Udp.parsePacket();
    //Serial.print("Received (IP/Size/Data): ");
    //Serial.print(WiFi.localIP());Serial.print(" / ");
    //Serial.print(packetSize);Serial.println(" / ");

    String receivedString = "";
    
    if (packetSize)
    {
       int len = Udp.read(packetBuffer, 512);

       int n = 0;
       for(int i=0; i<packetSize; i = i+3)
       {
          leds[n] = CRGB(packetBuffer[i],packetBuffer[i+1],packetBuffer[i+2]); ;
          n++;

          if(n>=NUM_LEDS){
            break;
          }
       }
    }
   
    FastLED.show();
    //delay(300);
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ReceivedMessage.h>

WiFiUDP Udp;
const int udp_port = 5000;
ReceivedMessage message;


void setup() {
  
  Serial.begin(115200);
  WiFi.softAP("ClockRocket", "123");
  Udp.begin(udp_port);

}

void loop() {

  int packetSize = Udp.parsePacket();
  

  if (packetSize)
  {
      bool wellFormedPackage = packetSize == sizeof(message);

      if(wellFormedPackage)
      {
        Udp.read((char*)&message, sizeof(message));
        //Do code with message here
      }
      else
      {
        Udp.flush();
      }      
  }
}

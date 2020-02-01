#include <Arduino.h>
#include <RocketServer.h>

RocketServer server;


void setup() {
  
  Serial.begin(115200);
  server.Setup(5000);

}

void loop() {

  server.Update();

}

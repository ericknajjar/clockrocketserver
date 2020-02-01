#include <Arduino.h>
#include <RocketServer.h>

RocketServer server(500);


void setup() {
  
  Serial.begin(115200);
  server.Setup();

}

void loop() {

  server.Update();

}

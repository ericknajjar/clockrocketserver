#include <Arduino.h>
#include <RocketServer.h>
#include <RocketGameplay.h>

RocketGameplay gameplay;

RocketServer<RocketGameplay> server(&gameplay);


void setup() {
  
  Serial.begin(115200);
  server.Setup(5000);
  
}

void loop() {

  server.Update();

}

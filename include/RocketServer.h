#ifndef ROCKET_SERVER_H
#define ROCKET_SERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ReceivedMessage.h>

class RocketServer
{
    public:
        RocketServer(int udpPort)
        {
            udp_port = udpPort;
        }

        inline void Setup()
        {
              WiFi.softAP("ClockRocket", "123");
              Udp.begin(udp_port);
        }

        inline void Update()
        {
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

    private:
        WiFiUDP Udp;
        int udp_port = 5000;
        ReceivedMessage message;
};


#endif //ROCKET_SERVER_H
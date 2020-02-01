#ifndef ROCKET_SERVER_H
#define ROCKET_SERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ReceivedMessage.h>
#include <ConnectionResponseMesssage.h>
#include <functional>


const IPAddress LOCAL_HOST = IPAddress(127,0,0,1);

class RocketServer
{
    public:
        RocketServer() 
        {
            m_currentState = std::bind(&RocketServer::WaitingForConnectionState,this);
        }

        inline void Setup(uint16_t udpPot)
        {
              WiFi.softAP("ClockRocket", "123");
              m_udp.begin(udpPot);
        }

        template<class T> void  Send(const T& message)
        {
            Send(message,m_connectedIp,m_connectedPort);
        }

        inline bool IsConnected()
        {
            return m_connectedIp != LOCAL_HOST;
        }

        inline void Update()
        {
            m_currentState();
        }

    private:

        template<class T> void  Send(const T& message, const IPAddress& address,uint16_t port)
        {
             m_udp.beginPacket(address,port);
             byte* toSend = nullptr;
             uint16_t size = message.AsByteArray(toSend);
             m_udp.write(toSend,size);
             m_udp.endPacket();
        }

        inline void ReceivingGameCommandsState()
        {

        }

        inline void WaitingForConnectionState()
        {
            int packetSize = m_udp.parsePacket();

            if (packetSize)
            {
                bool wellFormedPackage = packetSize == sizeof(message);

                if(wellFormedPackage)
                {
                    m_udp.read((byte*)&message, sizeof(message));

                    if(message.header == ReceivedMessageType::CONNECT)
                    {
                        ConnectionResponseMessage response(true);
                        if(m_connectedIp == LOCAL_HOST)
                        {
                            m_connectedIp = m_udp.remoteIP();
                            m_connectedPort = m_udp.remotePort();
                            m_currentState = std::bind(&RocketServer::ReceivingGameCommandsState,this);
                        }
                        else
                        {
                            response = ConnectionResponseMessage(false);
                           
                        }
                        Send(response,m_udp.remoteIP(), m_udp.remotePort());
                    }

                }
                else
                {
                    m_udp.flush();
                }      
            }
        }

        

        IPAddress m_connectedIp = LOCAL_HOST;
        uint16_t m_connectedPort;

        WiFiUDP m_udp;
        ReceivedMessage message;
        std::function<void(void)> m_currentState;
        
};


#endif //ROCKET_SERVER_H
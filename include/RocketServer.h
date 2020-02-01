#ifndef ROCKET_SERVER_H
#define ROCKET_SERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ReceivedMessage.h>
#include <ConnectionResponseMesssage.h>
#include <functional>
#include <ScoresResponseMessage.h>

const IPAddress LOCAL_HOST = IPAddress(127,0,0,1);

template<class Gameplay> class RocketServer
{
    public:
        RocketServer(Gameplay* gameplayMessageHandler) 
        {
            m_currentState = std::bind(&RocketServer::WaitingForConnectionState,this,std::placeholders::_1);
            m_gameplayMessageHandler = gameplayMessageHandler;
        }

        inline void Setup(uint16_t udpPot)
        {
              WiFi.softAP("ClockRocket", "12345678");
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
            int packetSize = m_udp.parsePacket();
            if (packetSize)
            {
                ReceivedMessage message;
                bool wellFormedPackage = packetSize == sizeof(message);

                if(wellFormedPackage)
                {
                    m_currentState(message);
                }
                else
                {
                    m_udp.flush();
                }
            }
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

        inline void ReceivingGameCommandsState(const ReceivedMessage&  message)
        {
            switch (message.header )
            {
            case ReceivedMessageType::DISCONNECT:
                break;

            case ReceivedMessageType::CHECK_SCORE:
            {
                ScoresResponseMessage scoreMessage = m_gameplayMessageHandler->GetScores();
                Send(scoreMessage);
                break;
            
            }

            default:
                return;
            }

        }

        inline void WaitingForConnectionState(const ReceivedMessage&  message)
        {
            if(message.header == ReceivedMessageType::CONNECT)
            {
                ConnectionResponseMessage response(true);
                if(m_connectedIp == LOCAL_HOST)
                {
                    m_connectedIp = m_udp.remoteIP();
                    m_connectedPort = m_udp.remotePort();
                    m_currentState = std::bind(&RocketServer::ReceivingGameCommandsState,this,std::placeholders::_1);
                }
                else
                {
                    response = ConnectionResponseMessage(false);
                
                }
                Send(response,m_udp.remoteIP(), m_udp.remotePort());
            }    
        }

        IPAddress m_connectedIp = LOCAL_HOST;
        uint16_t m_connectedPort;
        WiFiUDP m_udp;
        std::function<void(const ReceivedMessage&)> m_currentState;
        Gameplay* m_gameplayMessageHandler;
        
};


#endif //ROCKET_SERVER_H
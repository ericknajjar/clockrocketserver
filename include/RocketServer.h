#ifndef ROCKET_SERVER_H
#define ROCKET_SERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <GameplayMessage.h>
#include <ConnectionResponseMesssage.h>
#include <ConnectionMessage.h>
#include <ScoresResponseMessage.h>
#include <functional>

const IPAddress LOCAL_HOST = IPAddress(127,0,0,1);

template<class Gameplay> class RocketServer
{
    public:
        RocketServer(Gameplay* gameplayMessageHandler) 
        {
            m_currentState = std::bind(&RocketServer::WaitingForConnectionState,this);
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

        inline void ForceDisconnect(bool send)
        {
            if(send)
            {
                ConnectionResponseMessage response(false);
                Send(response,m_connectedIp, m_connectedPort);
            }

            m_connectedIp = LOCAL_HOST;
            m_currentState = std::bind(&RocketServer::WaitingForConnectionState,this);
        }

        inline void Update()
        {
            int packetSize = m_udp.parsePacket();
            if (packetSize)
            {
                if(!m_currentState())
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

        inline bool ReceivingGameCommandsState()
        {
            if(IsMessageFromConnected())
            {
                GameplayMessage message;
                int packetSize = Read(message);
                bool wellFormedPackage = packetSize == sizeof(message);
                
                if(!wellFormedPackage)
                    return false;

                switch (message.header)
                {

                    case ReceivedMessageType::DISCONNECT:
                    {
                        ForceDisconnect(false);
                        break;
                    }
                        
                    case ReceivedMessageType::CHECK_SCORE:
                    {
                        ScoresResponseMessage scoreMessage = m_gameplayMessageHandler->GetScores();
                        Send(scoreMessage);
                        break;
                    
                    }

                    case ReceivedMessageType::UP_PRESSED:
                    {
                        m_gameplayMessageHandler->UpdateUpPressed(true);
                        break;
                    }

                    case ReceivedMessageType::UP_FREE:
                    {
                        m_gameplayMessageHandler->UpdateUpPressed(false);
                        break;
                    }

                    default:
                    {
                        break;
                    }
                    
                }
                
                return true;
            }
            else
            {
                ConnectionResponseMessage response(false);
                Send(response,m_udp.remoteIP(), m_udp.remotePort());
                return false;
            }
            
            
        }

        template<class T> int Read(T& message)
        {
            return m_udp.read((char*)&message,sizeof(message));
        }

        bool IsMessageFromConnected()
        {
            return m_udp.remoteIP() == m_connectedIp;
        }

        inline bool WaitingForConnectionState()
        {
            ConnectionMessage message;
            Read(message);

            if(message.header == ReceivedMessageType::CONNECT)
            {
                
                m_connectedIp = m_udp.remoteIP();
                m_connectedPort = m_udp.remotePort();
  
                ConnectionResponseMessage response(true);
                Send(response,m_connectedIp, m_connectedPort);
                m_gameplayMessageHandler->NewGameStarted(message.name);

               m_currentState = std::bind(&RocketServer::ReceivingGameCommandsState,this);
               return true;
                
            }    

            return false;
        }

        IPAddress m_connectedIp = LOCAL_HOST;
        uint16_t m_connectedPort;
        WiFiUDP m_udp;
        std::function<bool(void)> m_currentState;
        Gameplay* m_gameplayMessageHandler;
        
};


#endif //ROCKET_SERVER_H
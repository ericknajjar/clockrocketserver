#ifndef CONNECTION_RESPONSE_MESSAGE_H
#define CONNECTION_RESPONSE_MESSAGE_H

#include <Arduino.h>
#include <SentMessageType.h>

struct ConnectionResponseMessage
{
    ConnectionResponseMessage(bool accepted)
    {
        header = accepted?SentMessageType::CONNECTION_ACCEPTED:SentMessageType::CONNECTION_REFUSED;
    }

    private:
        byte header: 2;
    
};




#endif//CONNECTION_RESPONSE_MESSAGE_H
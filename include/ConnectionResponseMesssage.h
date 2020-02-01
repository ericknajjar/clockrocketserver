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

    inline uint16_t AsByteArray(byte*& ret) const
    {
        ret = (byte*)this;
        return sizeof(ConnectionResponseMessage);
    }

    private:
        byte header: 3;
    
};




#endif//CONNECTION_RESPONSE_MESSAGE_H
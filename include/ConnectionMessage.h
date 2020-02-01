#ifndef CONNECTION_MESSAGE_H
#define CONNECTION_MESSAGE_H
#include <Arduino.h>
#include <ReceivedMessageType.h>

struct ConnectionMessage
{
    ReceivedMessageType header: 3;
    byte name[11];
};


#endif//CONNECTION_MESSAGE_H

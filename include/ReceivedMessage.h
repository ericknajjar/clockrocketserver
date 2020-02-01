#ifndef RECEIVED_MESSAGE_H
#define RECEIVED_MESSAGE_H
#include <Arduino.h>
#include <ReceivedMessageType.h>

struct ReceivedMessage
{
    ReceivedMessageType header: 6;
    byte payload: 2;
};


#endif//RECEIVED_MESSAGE_H

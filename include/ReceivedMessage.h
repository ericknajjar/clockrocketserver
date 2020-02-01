#ifndef RECEIVED_MESSAGE_H
#define RECEIVED_MESSAGE_H
#include <Arduino.h>
#include <ReceivedMessageType.h>

struct ReceivedMessage
{
    ReceivedMessageType header: 3;
    byte payload: 5;
};


#endif//RECEIVED_MESSAGE_H

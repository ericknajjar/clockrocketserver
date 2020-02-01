#ifndef RECEIVED_MESSAGE_H
#define RECEIVED_MESSAGE_H
#include <Arduino.h>

struct ReceivedMessage
{
    byte header: 6;
    byte payload: 2;
};

#endif//RECEIVED_MESSAGE_H

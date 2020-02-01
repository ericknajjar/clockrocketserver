#ifndef RECEIVED_MESSAGE_TYPE_H
#define RECEIVED_MESSAGE_TYPE_H
#include <Arduino.h>

enum ReceivedMessageType: byte
{
    CONNECT=0,CHECK_SCORE=1
};

#endif//RECEIVED_MESSAGE_TYPE_H
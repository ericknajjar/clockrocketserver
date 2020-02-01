#ifndef GAMEPLAY_MESSAGE_H
#define GAMEPLAY_MESSAGE_H
#include <Arduino.h>
#include <ReceivedMessageType.h>

struct GameplayMessage
{
    ReceivedMessageType header: 3;
    byte payload: 5;
};


#endif//GAMEPLAY_MESSAGE_H

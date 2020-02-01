#ifndef SENT_MESSAGE_TYPE_H
#define SENT_MESSAGE_TYPE_H
#include <Arduino.h>

enum SentMessageType: byte
{
    CONNECTION_REFUSED=0,CONNECTION_ACCEPTED=1,SCORES=2
};

#endif//SENT_MESSAGE_TYPE_H
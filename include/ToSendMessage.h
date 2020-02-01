#ifndef TO_SEND_MESSAGE_H
#define TO_SEND_MESSAGE_H

#include <Arduino.h>


struct ToSendMessage
{
    
    byte header: 2;
    byte payload: 6;

    static ToSendMessage ConnectionAccepted();
    static ToSendMessage ConnectionRefused();
    
};




#endif//TO_SEND_MESSAGE_H
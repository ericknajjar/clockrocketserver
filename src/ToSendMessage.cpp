#include "headers/ToSendMessage.h"

ToSendMessage ToSendMessage::ConnectionRefused()
{
    ToSendMessage ret = ToSendMessage();
    ret.header = 1;
    ret.payload = 0;

    return ret;
}

ToSendMessage ToSendMessage::ConnectionAccepted()
{
    static byte s_nexClientId = 0;

    ToSendMessage ret = ToSendMessage();
    ret.header = 0;

    ret.payload = s_nexClientId;

    if(++s_nexClientId == 64)
        s_nexClientId = 0;

    return ret;
}
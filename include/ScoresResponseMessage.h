#ifndef SCORES_RESPONSE_MESSAGE_H
#define SCORES_RESPONSE_MESSAGE_H

#include <Arduino.h>
#include <SentMessageType.h>
#include <ScoreEntry.h>

struct ScoresResponseMessage
{
    ScoresResponseMessage(): m_numElements(0)
    {
        m_header = SentMessageType::SCORES;
    }

    ScoresResponseMessage(const ScoreEntry& first): ScoresResponseMessage()
    {
        m_numElements = 1;
        m_entrys[0] = first;
    }

    ScoresResponseMessage(const ScoreEntry& first,const ScoreEntry& second): ScoresResponseMessage(first)
    {
        m_numElements = 2;
        m_entrys[1] = second;
    }

    ScoresResponseMessage(const ScoreEntry& first,const ScoreEntry& second,const ScoreEntry& third): ScoresResponseMessage(first,second)
    {
        m_numElements = 3;
        m_entrys[2] = third;
    }

    ScoresResponseMessage(const ScoreEntry& first,const ScoreEntry& second,const ScoreEntry& third,const ScoreEntry& forth): ScoresResponseMessage(first,second,third)
    {
        m_numElements = 4;
        m_entrys[4] = forth;
    }

    ScoresResponseMessage(const ScoreEntry& first,const ScoreEntry& second,const ScoreEntry& third,const ScoreEntry& forth,const ScoreEntry& fifth): ScoresResponseMessage(first,second,third,fifth)
    {
        m_numElements = 5;
        m_entrys[5] = forth;
    }

    inline uint16_t AsByteArray(byte*& ret) const
    { 
        ret = (byte*)this;

        size_t maxSize = sizeof(ScoresResponseMessage);
        size_t reductionCount = (5-m_numElements);
    
        return maxSize-(reductionCount*sizeof(ScoreEntry));
    }

    private:
        byte m_header: 3;
        byte m_numElements: 3;
        ScoreEntry m_entrys[5];

};

#endif//SCORES_RESPONSE_MESSAGE_H
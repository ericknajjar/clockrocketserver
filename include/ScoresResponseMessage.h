#ifndef SCORES_RESPONSE_MESSAGE_H
#define SCORES_RESPONSE_MESSAGE_H

#include <Arduino.h>
#include <SentMessageType.h>
#include <ScoreEntry.h>

struct ScoresResponseMessage
{
    ScoresResponseMessage():m_firstElement(0),m_secondElement(0),m_thirdElement(0)
    {
        m_header = SentMessageType::SCORES;
    }

    ScoresResponseMessage(const ScoreEntry& first): ScoresResponseMessage()
    {
        m_firstElement = 1;
        m_entrys[0] = first;
    }

    ScoresResponseMessage(const ScoreEntry& first,const ScoreEntry& second): ScoresResponseMessage(first)
    {
        m_secondElement = 1;
        m_entrys[1] = second;
    }

    ScoresResponseMessage(const ScoreEntry& first,const ScoreEntry& second,const ScoreEntry& third): ScoresResponseMessage(first,second)
    {
        m_thirdElement = 1;
        m_entrys[2] = third;
    }

    inline uint16_t AsByteArray(byte*& ret) const
    { 
        ret = (byte*)this;

        size_t maxSize = sizeof(ScoresResponseMessage);
        size_t reductionCount = 0;

        if(m_firstElement == 1)
            ++reductionCount;

        if(m_secondElement == 1)
            ++reductionCount;

        if(m_thirdElement == 1)
            ++reductionCount;

    
        return maxSize-(reductionCount*sizeof(ScoreEntry));
    }

    private:
        byte m_header: 3;
        byte m_firstElement: 1;
        byte m_secondElement: 1;
        byte m_thirdElement: 1;
        ScoreEntry m_entrys[3];

};

#endif//SCORES_RESPONSE_MESSAGE_H
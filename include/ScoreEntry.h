#ifndef SCORES_ENTRY_H
#define SCORES_ENTRY_H

#include <Arduino.h>
#include <SentMessageType.h>

struct ScoreEntry
{
    byte name[3];
    uint32_t score;
};

#endif//SCORES_ENTRY_H
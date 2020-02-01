#ifndef ROCKET_GAMEPLAY_H
#define ROCKET_GAMEPLAY_H

#include <Arduino.h>

#include <ScoresResponseMessage.h>
class RocketGameplay
{
    public:
        inline ScoresResponseMessage GetScores()
        {
            return ScoresResponseMessage();
        }

        inline void UpdateUpPressed(bool val)
        {

        }

        inline void NewGameStarted(byte name[11])
        {

        }
};

#endif //ROCKET_GAMEPLAY_H

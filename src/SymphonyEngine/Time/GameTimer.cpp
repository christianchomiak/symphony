#include "GameTimer.h"

#include "GameTimerWindows.h"

namespace Symphony
{
    GameTimer* GameTimer::CreateTimer()
    {
        return new GameTimerWindows();
    }
}


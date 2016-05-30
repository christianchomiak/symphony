#include "GameTimerWindows.h"

namespace Symphony
{
    
    GameTimerWindows::GameTimerWindows()
    {
        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);

        lastTime = GetMS();
        div1000ByFreq = 1000.0 / (double)frequency.QuadPart;
    }

    float GameTimerWindows::GetMS()
    {
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);
        return (float)((t.QuadPart - start.QuadPart) *div1000ByFreq); // 1000.0 / frequency.QuadPart);
    }

    float GameTimerWindows::GetTimedMS()
    {
        float a = GetMS();
        float b = a - lastTime;
        lastTime = a;
        return b;
    }

    void GameTimerWindows::Update()
    {
        deltaTime = GetTimedMS() / 1000.0f;
    }
}
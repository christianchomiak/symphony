#pragma once

#include "GameTimer.h"

#include <windows.h>
#include <stdio.h>
//#include <io.h>

namespace Symphony
{
    class GameTimerWindows : public GameTimer
    {   
    public:
        GameTimerWindows();

        //How many milliseconds have passed since the GameTimer was created
        virtual float GetMS() override;
        
        virtual void Update() override;

        inline float GetDeltaTime() override
        {
            return deltaTime;
        }

    protected:
        LARGE_INTEGER    start;            //Start of timer
        LARGE_INTEGER    frequency;        //Ticks Per Second

        float lastTime;                    //Last time GetTimedMS was called
        double div1000ByFreq;              //Caches a common operation over `frequency`

        //How many milliseconds have passed since GetTimedMS was last called
        virtual float GetTimedMS() override;

    private:
        GameTimerWindows(GameTimerWindows const&) = delete;
        void operator=(GameTimerWindows const&) = delete;
    };
}
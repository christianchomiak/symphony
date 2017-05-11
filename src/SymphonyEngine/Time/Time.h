#pragma once

#include <iostream>
//#include "../Utilities/Singleton.h"
#include "../Macros/ClassMacros.h"

namespace Symphony
{
    class Time
    {
        friend class SymphonyEngine;

    public:
        NO_DEFAULT_CONSTRUCTORS(Time)

        static inline float DeltaTime();
        static inline float TrueDeltaTime();
        
        static bool IsPaused();

    protected:
        static double deltaTime;
        static double trueDeltaTime;
        static double latestTime; //Latest queried time
        static bool paused;
        
        static double Update();
        static double GetCurrentTime();
    };

    inline bool Time::IsPaused()
    {
        return paused;
    }

    inline float Time::DeltaTime()
    {
        return (float)deltaTime;
    }

    inline float Time::TrueDeltaTime()
    {
        return (float)trueDeltaTime;
    }

}
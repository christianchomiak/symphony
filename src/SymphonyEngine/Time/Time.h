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
        
    protected:
        static double deltaTime;
        static double latestTime; //Latest queried time

        static double Update();
        static double GetCurrentTime();
    };

    inline float Time::DeltaTime()
    {
        return (float)deltaTime;
    }

}
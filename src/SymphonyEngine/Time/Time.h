#pragma once

#include <iostream>
#include "../Utilities/Singleton.h"
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
        static double currentTime;
        
        static void Update();
    };

    inline float Time::DeltaTime() 
    { 
        return (float) deltaTime;
    }
}
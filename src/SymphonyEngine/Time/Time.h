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

        static double currentTime;
        static double deltaTime;

        static void Update();
    };

    inline float Time::DeltaTime() 
    { 
        return (float)deltaTime;
    }



    /*class Time : public Singleton<Time>
    {
        friend class Singleton<Time>;
        friend class SymphonyEngine;
    public:
        //How many milliseconds have passed since the timer was created
        inline double GetMS() const { return currentTime; }
        
        //How many seconds have passed since last frame
        inline float GetDeltaTime() const { return (float)deltaTime; }
        
        static inline double GetTimeSinceStart() { return Instance()->GetMS(); }
        static inline float DeltaTime() { return Instance()->GetDeltaTime(); }
        
    protected:
        double currentTime = 0.0;
        double deltaTime = 0.0;
        
        virtual void UpdateTime();
        static void Update() { return Instance()->UpdateTime(); }
        
    private:
        Time() { currentTime = 0.0; deltaTime = 0.0; };
        Time(Time const&) = delete;
        void operator=(Time const&) = delete;
    };*/
}
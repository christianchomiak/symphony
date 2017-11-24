#pragma once

#ifdef _WIN32
#   include <windows.h>
#endif

namespace Symphony
{
    class StopWatch
    {
    public:
        StopWatch() : elapsedTime(0.0), running(false)
        {
        }
        
        ~StopWatch()
        {
        }

        void Start();

        void Stop();

        inline double GetElapsedTime() const
        {
            return elapsedTime;
        }

    protected:
        bool running;

#ifdef _WIN32
        typedef LARGE_INTEGER MeasureType;
        LARGE_INTEGER frequency;
#else
        typedef double MeasureType;
#endif

        MeasureType startPoint;
        MeasureType stopPoint;

        double elapsedTime;
    };
}
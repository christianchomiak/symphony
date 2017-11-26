#include "StopWatch.h"
#include <Debugging/Debugging.h>

using namespace Symphony;

void StopWatch::Start()
{
    if (!running)
    {
        running = true;

#ifdef _WIN32
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startPoint);
#else
        startPoint  = 0.0;
        LogError("Empty implementation of the StopWatch class in this build.");
#endif

        elapsedTime = 0.0;
    }
    else
    {
        LogWarning("StopWatch is already running, stop it first!");
    }
}

void StopWatch::Stop()
{
    if (running)
    {
#ifdef _WIN32
        QueryPerformanceCounter(&stopPoint);

        elapsedTime = (stopPoint.QuadPart - startPoint.QuadPart) * 1000.0 / frequency.QuadPart;
#else
        stopPoint   = 0.0;
        elapsedTime = 0.0;

        LogError("Empty implementation of the StopWatch class in this build.");
#endif
        running = false;
    }
    else
    {
        LogWarning("StopWatch is not running, start it first!");
    }
}
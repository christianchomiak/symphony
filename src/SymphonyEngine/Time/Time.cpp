#include "Time.h"

#include <GLFW/glfw3.h>

namespace Symphony
{
    double Time::latestTime     = 0.0;
    double Time::deltaTime      = 0.0;
    double Time::trueDeltaTime  = 0.0;
    bool   Time::paused         = false;

    unsigned long long Time::frame = 0;
    
    double Time::Update()
    {
        double currentTime = glfwGetTime();
        trueDeltaTime      = currentTime - latestTime;
        latestTime         = currentTime;

        deltaTime = paused ? 0.0f : trueDeltaTime;

        return latestTime;
    }

    double Time::GetCurrentTime()
    {
        return glfwGetTime();
    }
}
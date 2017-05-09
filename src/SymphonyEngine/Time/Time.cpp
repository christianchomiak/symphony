#include "Time.h"

#include <GLFW/glfw3.h>

namespace Symphony
{
    double Time::latestTime = 0.0;
    double Time::deltaTime  = 0.0;

    double Time::Update()
    {
        double currentTime = glfwGetTime();
        deltaTime          = currentTime - latestTime;
        latestTime         = currentTime;

        return latestTime;
    }

    double Time::GetCurrentTime()
    {
        return glfwGetTime();
    }
}
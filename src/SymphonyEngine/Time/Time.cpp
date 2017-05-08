#include "Time.h"

#include <GLFW/glfw3.h>

namespace Symphony
{
    double Time::currentTime = 0.0;
    double Time::deltaTime   = 0.0;

    void Time::Update()
    {
        double current = glfwGetTime();
        deltaTime      = current - currentTime;
        currentTime    = current;
    }
}
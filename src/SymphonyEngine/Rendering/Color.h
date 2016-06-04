#pragma once

#include <glm/vec4.hpp>

namespace Symphony
{
    namespace Color
    {
        inline glm::vec4 White()    { return glm::vec4(1.f);                    }
        inline glm::vec4 Black()    { return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); }
        inline glm::vec4 Grey()     { return glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); }

        inline glm::vec4 Red()      { return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); }
        inline glm::vec4 Blue()     { return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); }
        inline glm::vec4 Green()    { return glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); }
        inline glm::vec4 Cyan()     { return glm::vec4(0.0f, 1.0f, 1.0f, 1.0f); }
        inline glm::vec4 Yellow()   { return glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); }
        inline glm::vec4 Magenta()  { return glm::vec4(1.0f, 0.0f, 1.0f, 1.0f); }
    }
}
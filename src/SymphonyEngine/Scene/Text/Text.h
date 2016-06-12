#pragma once

#include <string>

namespace Symphony
{
    struct Text
    {
    public:
        std::string content;
        glm::vec3 position;
        glm::vec3 color;
        float scale;

        Text()
            : content(""), scale(1.f), color(glm::vec3(1.0f, 1.0f, 1.0f))
        {

        }

        Text(const std::string& content, const glm::vec3& position, const glm::vec3& color, float scale)
            : content(content), position(position), color(color), scale(scale)
        {
        }
    };
}
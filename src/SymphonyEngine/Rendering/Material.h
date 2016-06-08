#pragma once

#include <glm/vec3.hpp>

namespace Symphony
{
    struct Material
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        Material()
            : ambient(glm::vec3(1.f)), diffuse(glm::vec3(1.f)), specular(glm::vec3(1.f)), shininess(0.1f)
        {
        }

        Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
            : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
        {
        }
    };
}
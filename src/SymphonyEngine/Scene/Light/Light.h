#pragma once

#include <glm/vec3.hpp>
#include "../GameObject.h"
#include "../../Rendering/Shader.h"

namespace Symphony
{
    class Light : public GameObject
    {
    public:
        Light();
        Light(const glm::vec3&, const glm::vec3&, const glm::vec3&);
        virtual ~Light() {};

        virtual void UpdateShader(const Shader*, int lightNumber = -1) const = 0;
    protected:
        glm::vec3 diffuse,
                  specular,
                  ambient;
    };
} 
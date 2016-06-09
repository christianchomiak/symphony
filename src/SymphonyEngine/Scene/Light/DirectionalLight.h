#pragma once

#include "Light.h"

namespace Symphony
{
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        DirectionalLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
        virtual ~DirectionalLight() {};
        virtual void UpdateShader(const Shader* s, int lightNumber = -1) const override;
    };
}
#pragma once

#include "Light.h"

namespace Symphony
{
    class PointLight : public Light
    {
    public:
        PointLight();
        PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
        PointLight(float radius, float constant, float linear, float quadratic);
        PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float radius, float constant, float linear, float quadratic);
        virtual ~PointLight() {};
        virtual void UpdateShader(const Shader* s) const override;

        void SetAttenuation(float radius, float constant, float linear, float quadratic);
    protected:
        float radius;
        float constantTerm;
        float linearTerm;
        float quadraticTerm;
    };
}
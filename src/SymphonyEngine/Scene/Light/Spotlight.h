#pragma once

#include "PointLight.h"

namespace Symphony
{
    class Spotlight : public PointLight
    {
    public:
        Spotlight();
        Spotlight(float cutoff, float outerCutOff);
        Spotlight(float cutoff, float outerCutOff, float constant, float linear, float quadratic);
        Spotlight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float cutoff, float outerCutOff);
        Spotlight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float cutoff, float outerCutOff,
                 float constant, float linear, float quadratic);
        virtual ~Spotlight() {};
        virtual void UpdateShader(const Shader* s) const override;

        void SetCutoff(float inner, float outer);
        float GetCutoff() const;
    protected:
        float cutoff;
        float outerCutOff;
        float cutoffProcessed, outerCutOffProcessed;
    };
}
#include "Spotlight.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <glm/geometric.hpp>

namespace Symphony
{
    Spotlight::Spotlight() : Spotlight(12.5f, 17.5f)
    { }

    Spotlight::Spotlight(float cutoff, float outerCutoff) : cutoff(cutoff), outerCutOff(outerCutoff)
    {
        cutoffProcessed = glm::cos(glm::radians(cutoff));
        outerCutOffProcessed = glm::cos(glm::radians(outerCutOff));
    }

    Spotlight::Spotlight(float cutoff, float outerCutoff, float constant, float linear, float quadratic)
        : PointLight(0.f, constant, linear, quadratic), cutoff(cutoff), outerCutOff(outerCutoff)
    {
        cutoffProcessed = glm::cos(glm::radians(cutoff));
        outerCutOffProcessed = glm::cos(glm::radians(outerCutOff));
    }

    Spotlight::Spotlight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float cutoff, float outerCutoff)
        : PointLight(ambient, diffuse, specular), cutoff(cutoff), outerCutOff(outerCutoff)
    {
        cutoffProcessed = glm::cos(glm::radians(cutoff));
        outerCutOffProcessed = glm::cos(glm::radians(outerCutOff));
    }

    Spotlight::Spotlight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float cutoff, float outerCutoff,
                         float constant, float linear, float quadratic)
        : PointLight(ambient, diffuse, specular, 0.f, constant, linear, quadratic), cutoff(cutoff), outerCutOff(outerCutoff)
    {
        cutoffProcessed = glm::cos(glm::radians(cutoff));
        outerCutOffProcessed = glm::cos(glm::radians(outerCutOff));
    }

    void Spotlight::UpdateShader(const Shader * s) const
    {
        glUniform1i(glGetUniformLocation(s->ID(), "light.type"), 1);

        glUniform3fv(glGetUniformLocation(s->ID(), "light.position"), 1, glm::value_ptr(transform.GetPosition()));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.direction"), 1, glm::value_ptr(transform.Forward()));

        glUniform3fv(glGetUniformLocation(s->ID(), "light.ambient"), 1, glm::value_ptr(ambient));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.diffuse"), 1, glm::value_ptr(diffuse));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.specular"), 1, glm::value_ptr(specular));
        
        //TO-DO: Attenuation is not working correctly
        //   Nevermind, it seems to work...for now. Let's keep an eye on it.
        glUniform1f(glGetUniformLocation(s->ID(), "light.constant"), constantTerm);
        glUniform1f(glGetUniformLocation(s->ID(), "light.linear"), linearTerm);
        glUniform1f(glGetUniformLocation(s->ID(), "light.quadratic"), quadraticTerm);

        glUniform1f(glGetUniformLocation(s->ID(), "light.cutOff"), cutoffProcessed);
        glUniform1f(glGetUniformLocation(s->ID(), "light.outerCutOff"), outerCutOffProcessed);
    }

    void Spotlight::SetCutoff(float inner, float outer)
    {
        cutoff = inner;
        outerCutOff = outerCutOff;
        cutoffProcessed = glm::cos(glm::radians(cutoff));
        outerCutOffProcessed = glm::cos(glm::radians(outerCutOff));
    }

    float Spotlight::GetCutoff() const
    {
        return cutoff;
    }
}
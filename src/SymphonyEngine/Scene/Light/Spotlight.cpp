#include "Spotlight.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <glm/geometric.hpp>

namespace Symphony
{
    Spotlight::Spotlight() : Spotlight(12.5f, 17.5f)
    { }

    Spotlight::Spotlight(float cutoff, float outerCutoff)
    {
        SetCutoff(cutoff, outerCutoff);
    }

    Spotlight::Spotlight(float cutoff, float outerCutoff, float constant, float linear, float quadratic)
        : PointLight(0.f, constant, linear, quadratic)
    {
        SetCutoff(cutoff, outerCutoff);
    }

    Spotlight::Spotlight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float cutoff, float outerCutoff)
        : PointLight(ambient, diffuse, specular)
    {
        SetCutoff(cutoff, outerCutoff);
    }

    Spotlight::Spotlight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float cutoff, float outerCutoff,
                         float constant, float linear, float quadratic)
        : PointLight(ambient, diffuse, specular, 0.f, constant, linear, quadratic)
    {
        SetCutoff(cutoff, outerCutoff);
    }

    void Spotlight::UpdateShader(const Shader * s, int lightNumber) const
    {
        GLuint typeLocation, positionLocation, directionLocation, ambientLocation, diffuseLocation, specularLocation;
        GLuint constantParamLocation, linearParamLocation, quadParamLocation;
        GLuint cutoffLocation, outerCutoffLocation;
        if (lightNumber < 0)
        {
            typeLocation = glGetUniformLocation(s->ID(), "light.type");
            directionLocation = glGetUniformLocation(s->ID(), "light.direction");
            positionLocation = glGetUniformLocation(s->ID(), "light.position");

            ambientLocation = glGetUniformLocation(s->ID(), "light.ambient");
            diffuseLocation = glGetUniformLocation(s->ID(), "light.diffuse");
            specularLocation = glGetUniformLocation(s->ID(), "light.specular");

            constantParamLocation = glGetUniformLocation(s->ID(), "light.constant");
            linearParamLocation = glGetUniformLocation(s->ID(), "light.linear");
            quadParamLocation = glGetUniformLocation(s->ID(), "light.quadratic");

            cutoffLocation = glGetUniformLocation(s->ID(), "light.cutOff");
            outerCutoffLocation = glGetUniformLocation(s->ID(), "light.outerCutOff");
        }
        else
        {
            std::string str = std::to_string(lightNumber);
            typeLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].type").c_str());
            directionLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].direction").c_str());
            positionLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].position").c_str());

            ambientLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].ambient").c_str());
            diffuseLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].diffuse").c_str());
            specularLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].specular").c_str());

            constantParamLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].constant").c_str());
            linearParamLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].linear").c_str());
            quadParamLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].quadratic").c_str());

            cutoffLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].cutOff").c_str());
            outerCutoffLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].outerCutOff").c_str());
        }

        glUniform1i(typeLocation, 1);
        glUniform3fv(directionLocation, 1, glm::value_ptr(transform.Forward()));
        glUniform3fv(positionLocation, 1, glm::value_ptr(transform.GetPosition()));

        glUniform3fv(ambientLocation, 1, glm::value_ptr(ambient));
        glUniform3fv(diffuseLocation, 1, glm::value_ptr(diffuse));
        glUniform3fv(specularLocation, 1, glm::value_ptr(specular));

        glUniform1f(constantParamLocation, constantTerm);
        glUniform1f(linearParamLocation, linearTerm);
        glUniform1f(quadParamLocation, quadraticTerm);

        glUniform1f(cutoffLocation, cutoffProcessed);
        glUniform1f(outerCutoffLocation, outerCutOffProcessed);
    }

    void Spotlight::SetCutoff(float inner, float outer)
    {
        cutoff = inner < outer ? inner : outer;
        outerCutOff = inner < outer ? outer : inner;

        cutoffProcessed = glm::cos(glm::radians(cutoff));
        outerCutOffProcessed = glm::cos(glm::radians(outerCutOff));
    }

    float Spotlight::GetCutoff() const
    {
        return cutoff;
    }
}
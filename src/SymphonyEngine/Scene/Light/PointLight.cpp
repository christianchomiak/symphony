#include "PointLight.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Symphony
{
    PointLight::PointLight()
    {
    }

    PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : Light(ambient, diffuse, specular)
    {
    }

    PointLight::PointLight(float radius, float constant, float linear, float quadratic)
        : radius(radius), constantTerm(constant), linearTerm(linear), quadraticTerm(quadratic)
    {
    }

    PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float radius, float constant, float linear, float quadratic)
        : Light(ambient, diffuse, specular), radius(radius), constantTerm(constant), linearTerm(linear), quadraticTerm(quadratic)
    {
    }

    void PointLight::UpdateShader(const Shader* s, int lightNumber) const
    {
        GLuint typeLocation, positionLocation, ambientLocation, diffuseLocation, specularLocation;
        GLuint constantParamLocation, linearParamLocation, quadParamLocation;

        if (lightNumber < 0)
        {
            typeLocation = glGetUniformLocation(s->ID(), "light.type");
            positionLocation = glGetUniformLocation(s->ID(), "light.position");

            ambientLocation = glGetUniformLocation(s->ID(), "light.ambient");
            diffuseLocation = glGetUniformLocation(s->ID(), "light.diffuse");
            specularLocation = glGetUniformLocation(s->ID(), "light.specular");

            constantParamLocation = glGetUniformLocation(s->ID(), "light.constant");
            linearParamLocation = glGetUniformLocation(s->ID(), "light.linear");
            quadParamLocation = glGetUniformLocation(s->ID(), "light.quadratic");
        }
        else
        {
            std::string str = std::to_string(lightNumber);
            typeLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].type").c_str());
            positionLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].position").c_str());

            ambientLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].ambient").c_str());
            diffuseLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].diffuse").c_str());
            specularLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].specular").c_str());

            constantParamLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].constant").c_str());
            linearParamLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].linear").c_str());
            quadParamLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].quadratic").c_str());
        }

        glUniform1i(typeLocation, -1);
        glUniform3fv(positionLocation, 1, glm::value_ptr(transform.GetPosition()));

        glUniform3fv(ambientLocation, 1, glm::value_ptr(ambient));
        glUniform3fv(diffuseLocation, 1, glm::value_ptr(diffuse));
        glUniform3fv(specularLocation, 1, glm::value_ptr(specular));

        glUniform1f(constantParamLocation, constantTerm);
        glUniform1f(linearParamLocation, linearTerm);
        glUniform1f(quadParamLocation, quadraticTerm);
    }

    //http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
    void PointLight::SetAttenuation(float radius, float constant, float linear, float quadratic)
    {
        this->radius = radius;
        constantTerm = constant;
        linearTerm = linear;
        quadraticTerm = quadratic;
    }
}
#include "DirectionalLight.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Symphony
{
    DirectionalLight::DirectionalLight()
    {
    }

    DirectionalLight::DirectionalLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : Light(ambient, diffuse, specular)
    {
    }
    
    void DirectionalLight::UpdateShader(const Shader * s, int lightNumber) const
    {
        GLuint typeLocation, directionLocation, ambientLocation, diffuseLocation, specularLocation;
        if (lightNumber < 0)
        {
            typeLocation = glGetUniformLocation(s->ID(), "light.type");
            directionLocation = glGetUniformLocation(s->ID(), "light.direction");

            ambientLocation = glGetUniformLocation(s->ID(), "light.ambient");
            diffuseLocation = glGetUniformLocation(s->ID(), "light.diffuse");
            specularLocation = glGetUniformLocation(s->ID(), "light.specular");
        }
        else
        {
            std::string str = std::to_string(lightNumber);
            typeLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].type").c_str());
            directionLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].direction").c_str());

            ambientLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].ambient").c_str());
            diffuseLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].diffuse").c_str());
            specularLocation = glGetUniformLocation(s->ID(), ("lights[" + str + "].specular").c_str());

        }
        
        glUniform1i(typeLocation, 0);
        glUniform3fv(directionLocation, 1, glm::value_ptr(transform.Forward()));

        glUniform3fv(ambientLocation, 1, glm::value_ptr(ambient));
        glUniform3fv(diffuseLocation, 1, glm::value_ptr(diffuse));
        glUniform3fv(specularLocation, 1, glm::value_ptr(specular));
    }
}
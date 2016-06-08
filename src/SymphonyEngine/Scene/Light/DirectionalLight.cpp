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
    
    void DirectionalLight::UpdateShader(const Shader * s) const
    {
        //Directional lights don't need positions, only directions.
        //We are using the same input, light.position, for such purpose.
        glUniform3fv(glGetUniformLocation(s->ID(), "light.direction"), 1, glm::value_ptr(transform.Forward()));
        //glUniform3fv(glGetUniformLocation(s->ID(), "light.direction"), 1, glm::value_ptr(glm::vec3(-0.2f, -1.0f, -0.3f)));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.ambient"), 1, glm::value_ptr(glm::vec3(ambient)));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.diffuse"), 1, glm::value_ptr(glm::vec3(diffuse)));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.specular"), 1, glm::value_ptr(glm::vec3(specular)));
    }
}
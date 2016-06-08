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

    void PointLight::UpdateShader(const Shader* s) const
    {
        glUniform1i(glGetUniformLocation(s->ID(), "light.type"), -1);

        glUniform3fv(glGetUniformLocation(s->ID(), "light.position"), 1, glm::value_ptr(transform.GetPosition()));

        glUniform3fv(glGetUniformLocation(s->ID(), "light.ambient"), 1, glm::value_ptr(ambient));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.diffuse"), 1, glm::value_ptr(diffuse));
        glUniform3fv(glGetUniformLocation(s->ID(), "light.specular"), 1, glm::value_ptr(specular));

        glUniform1f(glGetUniformLocation(s->ID(), "light.constant"), constantTerm);
        glUniform1f(glGetUniformLocation(s->ID(), "light.linear"), linearTerm);
        glUniform1f(glGetUniformLocation(s->ID(), "light.quadratic"), quadraticTerm);
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
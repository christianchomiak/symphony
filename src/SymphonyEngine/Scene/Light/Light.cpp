#include "Light.h"

#include "../../Rendering/Color.h"

namespace Symphony
{
    Light::Light()
    {
    }
    
    Light::Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : ambient(ambient), diffuse(diffuse), specular(specular)
    {
    }
}
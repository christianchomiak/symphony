#pragma once

//TO-DO: We don't need vector3 here as the struct is pretty simple
//       and could work by using floats directly
//#include <glm/vec3.hpp>
//#include <glm/geometric.hpp>

namespace Symphony
{
    struct Plane
    {
    public:
        float normalX, normalY, normalZ;
        float distance;
        
        Plane() {};
        Plane(float normalX, float normalY, float normalZ, float distance) //, bool normalise = false)
            : normalX(normalX), normalY(normalY), normalZ(normalZ), distance(distance)
        {
        }
        ~Plane() {};

        inline bool SphereInPlane(float positionX, float positionY, float positionZ, float radius) const
        {
            //return glm::dot(position, normal) + distance <= -radius;
            return ((positionX * normalX) + (positionY * normalY) + (positionZ * normalZ) + distance) > -radius;
        }
    };
}
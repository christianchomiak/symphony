#pragma once

#include "Plane.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace Symphony
{
    class Frustum
    {
    public:
        Plane planes[6];

        Frustum() {};
        void FromMatrix(const glm::mat4& mat);

        bool InsideFrustrum(const glm::vec3 position, float boundingRadius) const
        {
            /*if (!planes[0].SphereInPlane(position.x, position.y, position.z, boundingRadius)) return false;
            if (!planes[1].SphereInPlane(position.x, position.y, position.z, boundingRadius)) return false;
            if (!planes[2].SphereInPlane(position.x, position.y, position.z, boundingRadius)) return false;
            if (!planes[3].SphereInPlane(position.x, position.y, position.z, boundingRadius)) return false;
            if (!planes[4].SphereInPlane(position.x, position.y, position.z, boundingRadius)) return false;
            if (!planes[5].SphereInPlane(position.x, position.y, position.z, boundingRadius)) return false;*/
            return planes[0].SphereInPlane(position.x, position.y, position.z, boundingRadius)
                && planes[1].SphereInPlane(position.x, position.y, position.z, boundingRadius)
                && planes[2].SphereInPlane(position.x, position.y, position.z, boundingRadius)
                && planes[3].SphereInPlane(position.x, position.y, position.z, boundingRadius)
                && planes[4].SphereInPlane(position.x, position.y, position.z, boundingRadius)
                && planes[5].SphereInPlane(position.x, position.y, position.z, boundingRadius);
        }
    };
}
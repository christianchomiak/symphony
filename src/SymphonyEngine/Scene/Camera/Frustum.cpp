#include "Frustum.h"

#include <glm/gtc/matrix_access.hpp>

using namespace glm;

void Symphony::Frustum::FromMatrix(const mat4 & mat)
{
    vec4 xAxis = glm::row(mat, 0);
    vec4 yAxis = glm::row(mat, 1);
    vec4 zAxis = glm::row(mat, 2);
    vec4 wAxis = glm::row(mat, 3);

    vec4 temp[6];
    temp[0] = wAxis - xAxis;    //RIGHT
    temp[1] = wAxis + xAxis;    //LEFT

    temp[2] = wAxis + yAxis;    //BOTTOM
    temp[3] = wAxis - yAxis;    //TOP

    temp[4] = wAxis - zAxis;    //FAR
    temp[5] = wAxis + zAxis;    //NEAR

    for (size_t i = 0; i < 6; ++i)
    {
        float length = (temp[i].x * temp[i].x) + (temp[i].y * temp[i].y) + (temp[i].z * temp[i].z);
        temp[i] /= length;
        planes[i] = Plane(temp[i].x, temp[i].y, temp[i].z, temp[i].w);
    }
}

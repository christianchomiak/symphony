#pragma once

#include "Mesh.h"

namespace Symphony
{
    class MutableMesh : public Mesh
    {
    public:
        MutableMesh() {}
        bool UpdateVertices(glm::vec3* newVertexData, int numberOfNewVertexData);
    };
}
#include "MutableMesh.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files
#include <SOIL2/SOIL2.h>
#include <glm/geometric.hpp>

#include "../../Debugging/Debugging.h"

namespace Symphony
{
    bool MutableMesh::UpdateVertices(glm::vec3* newVertexData, int numberOfNewVertexData)
    {
        if (numberOfNewVertexData != numberOfVertices)
        {
            return false;
        }

        for (size_t i = 0; i < numberOfVertices; ++i)
        {
            vertices[i] = newVertexData[i];
        }

        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID[VERTEX_BUFFER]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, numberOfVertices * sizeof(glm::vec3), vertices);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return true;
    }
}
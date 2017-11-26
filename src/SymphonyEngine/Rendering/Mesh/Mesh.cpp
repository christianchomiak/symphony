#include "Mesh.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files
#include <SOIL2/SOIL2.h>
#include <glm/geometric.hpp>

#include <Debugging/Debugging.h>
#include "MutableMesh.h"

namespace Symphony
{
    Mesh::Mesh()
        : allowFaceCulling(true),
          numberOfVertices(0),
          numberOfIndices(0),
          vertices(nullptr),
          indices(nullptr),
          colours(nullptr),
          normals(nullptr),
          tangents(nullptr),
          textureCoordinates(nullptr),
          typeOfDraw(GL_STATIC_DRAW),
          typeOfPrimitive(GL_TRIANGLES)
    {

        for (unsigned short i = 0; i < MAX_BUFFER; ++i)
        {
            vboID[i] = 0;
        }
    }

    void Mesh::GenerateNormals()
    {
        glm::vec3 n;

        if (!normals)
        {
            normals = new glm::vec3[numberOfVertices];
        }

        for (uint i = 0; i < numberOfVertices; ++i)
        {
            normals[i] = glm::vec3();
        }

        if (indices) //Generate per-vertex normals
        {
            uint a;
            uint b;
            uint c;

            for (uint i = 0; i < numberOfIndices; i += 3)
            {
                a = indices[i];
                b = indices[i + 1];
                c = indices[i + 2];

                n = glm::cross(vertices[b] - vertices[a], vertices[c] - vertices[a]);

                normals[a] += n;
                normals[b] += n;
                normals[c] += n;
            }
        }
        else //It's just a list of triangles, so generate face normals
        {
            for (uint i = 0; i < numberOfVertices; i += 3)
            {
                glm::vec3& a = vertices[i];
                glm::vec3& b = vertices[i + 1];
                glm::vec3& c = vertices[i + 2];

                n = glm::cross(b - a, c - a);

                normals[i] = n;
                normals[i + 1] = n;
                normals[i + 2] = n;
            }
        }

        //std::cout << "Number of indices: " << numberOfIndices << std::endl;

        //TO-DO: this could be done inside the previous FORs
        for (uint i = 0; i < numberOfVertices; ++i)
        {
            glm::normalize(normals[i]);
        }
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(MAX_BUFFER, vboID);

        delete[] vertices;
        delete[] indices;
        delete[] colours;
        delete[] normals;
        delete[] textureCoordinates;
    }

    //TO-DO: Could it be benefitial to cache the result of operations such as `numberOfVertices * sizeof(glm::vecX)`?
    void Mesh::BufferData() const
    {
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        
        glGenBuffers(1, &vboID[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vboID[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), vertices, typeOfDraw);
        glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_BUFFER);

        if (colours)
        {
            glGenBuffers(1, &vboID[COLOUR_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[COLOUR_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec4), colours, typeOfDraw);

            glEnableVertexAttribArray(COLOUR_BUFFER);
            glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (textureCoordinates)
        {
            glGenBuffers(1, &vboID[TEXTURE_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[TEXTURE_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec2), textureCoordinates, typeOfDraw);

            glEnableVertexAttribArray(TEXTURE_BUFFER);
            glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (indices)
        {
            glGenBuffers(1, &vboID[INDEX_BUFFER]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[INDEX_BUFFER]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(GLuint), indices, typeOfDraw);
        }

        if (normals)
        {
            glGenBuffers(1, &vboID[NORMAL_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[NORMAL_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), normals, typeOfDraw);

            glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(NORMAL_BUFFER);
        }
        
        if (tangents)
        {
            glGenBuffers(1, &vboID[TANGENT_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[TANGENT_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), tangents, typeOfDraw); //texture.textureCoordinates

            glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(TANGENT_BUFFER);
        }

        glBindVertexArray(0);
    }

    void Mesh::Render() const
    {
        glBindVertexArray(vaoID);
        
        if (vboID[INDEX_BUFFER])
        {
            glDrawElements(typeOfPrimitive, numberOfIndices, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(typeOfPrimitive, 0, numberOfVertices);
        }

        glBindVertexArray(0);
    }

    /*bool Mesh::UpdateVertices(glm::vec3* newVertexData, int numberOfNewVertexData)
    {
        if (numberOfNewVertexData != numberOfVertices) return false;

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
    }*/
}


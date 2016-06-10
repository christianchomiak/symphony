#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Color.h" //Already includes <glm/vec4.hpp>

namespace Symphony
{
    enum MeshBuffer 
    {
        VERTEX_BUFFER,      //layout(location = 0)
        COLOUR_BUFFER,      //layout(location = 1)
        TEXTURE_BUFFER,     //layout(location = 2)
        NORMAL_BUFFER,      //layout(location = 3)
        TANGENT_BUFFER,     //layout(location = 4)
        INDEX_BUFFER,       //layout(location = 5)
        MAX_BUFFER
    };

    class Mesh
    {
    public:
        bool allowFaceCulling;

        ~Mesh();
        void BufferData();
        void Render();
        bool AllowFaceCulling() const;
    protected:
        unsigned int vaoID;
        unsigned int vboID[MAX_BUFFER];
        unsigned int typeOfPrimitive;

        unsigned int numberOfVertices,
               numberOfIndices;

        unsigned int* indices;
        glm::vec3 *vertices,
                  *normals,
                  *tangents;
        glm::vec2 *textureCoordinates;
        glm::vec4 *colours;

    protected:
        Mesh();

        void GenerateNormals();
    public:
        static Mesh* Triangle();
        static Mesh* Quad();
        static Mesh* Cube();
        static Mesh* HeightMap(const char* heigtmapFileName, float sizeX, float sizeZ, float maxHeight = 1.f);
        static Mesh* Surface(size_t width, size_t height, float sizeX, float sizeZ);
        static Mesh* CoordinateSystem(float size = 1.f);
    };

    inline bool Mesh::AllowFaceCulling() const
    {
        return allowFaceCulling;
    }
}
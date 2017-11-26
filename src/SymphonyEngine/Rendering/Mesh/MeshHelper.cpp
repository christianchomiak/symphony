#include "MeshHelper.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files
#include <SOIL2/SOIL2.h>
#include <glm/geometric.hpp>

#include <Debugging/Debugging.h>
#include "MutableMesh.h"

namespace Symphony
{
    Mesh* MeshHelper::CreateTriangle()
    {
        Mesh* mesh = new Mesh();

        mesh->typeOfPrimitive = GL_TRIANGLES;

        mesh->numberOfVertices = 3;
        mesh->vertices = new glm::vec3[mesh->numberOfVertices];
        mesh->vertices[0] = glm::vec3(-1, -1, 0);
        mesh->vertices[1] = glm::vec3(1, -1, 0);
        mesh->vertices[2] = glm::vec3(0, 1, 0);

        mesh->colours = new glm::vec4[mesh->numberOfVertices];
        mesh->colours[0] = Color::RED;    //Color::White();
        mesh->colours[1] = Color::GREEN;  //Color::White();
        mesh->colours[2] = Color::BLUE;   //Color::White();

        mesh->numberOfIndices = 3;
        mesh->indices = new GLuint[mesh->numberOfIndices];
        mesh->indices[0] = 0;
        mesh->indices[1] = 1;
        mesh->indices[2] = 2;

        mesh->textureCoordinates = new glm::vec2[mesh->numberOfVertices];
        mesh->textureCoordinates[0] = glm::vec2(0.5f, 0.0f);
        mesh->textureCoordinates[1] = glm::vec2(1.0f, 1.0f);
        mesh->textureCoordinates[2] = glm::vec2(0.0f, 1.0f);

        mesh->BufferData();

        return mesh;
    }

    Mesh* MeshHelper::CreateQuad()
    {
        Mesh* mesh = new Mesh();
        mesh->typeOfPrimitive = GL_TRIANGLE_STRIP;

        float v = 1.0f;
        mesh->numberOfVertices = 4;
        mesh->vertices = new glm::vec3[mesh->numberOfVertices];
        mesh->vertices[0] = glm::vec3(-v, -v, 0.0f);
        mesh->vertices[1] = glm::vec3(v, -v, 0.0f);
        mesh->vertices[2] = glm::vec3(-v, v, 0.0f);
        mesh->vertices[3] = glm::vec3(v, v, 0.0f);

        mesh->numberOfIndices = 4;
        mesh->indices = new GLuint[mesh->numberOfIndices];
        mesh->indices[0] = 0;
        mesh->indices[1] = 1;
        mesh->indices[2] = 2;
        mesh->indices[3] = 3;

        mesh->colours = new glm::vec4[mesh->numberOfVertices];
        mesh->colours[0] = Color::RED;
        mesh->colours[1] = Color::GREEN;
        mesh->colours[2] = Color::BLUE;
        mesh->colours[3] = Color::YELLOW;

        mesh->normals = new glm::vec3[mesh->numberOfVertices];
        mesh->normals[0] = glm::vec3(0, 0, 1);
        mesh->normals[1] = glm::vec3(0, 0, 1);
        mesh->normals[2] = glm::vec3(0, 0, 1);
        mesh->normals[3] = glm::vec3(0, 0, 1);

        mesh->tangents = new glm::vec3[mesh->numberOfVertices];
        mesh->tangents[0] = glm::vec3(1, 0, 0);
        mesh->tangents[1] = glm::vec3(1, 0, 0);
        mesh->tangents[2] = glm::vec3(1, 0, 0);
        mesh->tangents[3] = glm::vec3(1, 0, 0);

        mesh->textureCoordinates = new glm::vec2[mesh->numberOfVertices];
        mesh->textureCoordinates[0] = glm::vec2(0.f, 0.f);
        mesh->textureCoordinates[1] = glm::vec2(1.f, 0.f);
        mesh->textureCoordinates[2] = glm::vec2(0.f, 1.f);
        mesh->textureCoordinates[3] = glm::vec2(1.f, 1.f);

        mesh->BufferData();

        return mesh;
    }

    Mesh* MeshHelper::CreateCube(float textureRepetitionFactor)
    {
        Mesh* mesh = new Mesh();

        mesh->allowFaceCulling = false;

        mesh->typeOfPrimitive = GL_TRIANGLES;

        float v = 0.5f;

        ///VERTEX DATA
        mesh->numberOfVertices = 36;
        mesh->vertices = new glm::vec3[mesh->numberOfVertices];

        uint index = 0;
        //Bottom
        mesh->vertices[index++] = glm::vec3(-v, -v, -v);
        mesh->vertices[index++] = glm::vec3(v, -v, -v);
        mesh->vertices[index++] = glm::vec3(-v, -v, v);
        mesh->vertices[index++] = glm::vec3(v, -v, -v);
        mesh->vertices[index++] = glm::vec3(v, -v, v);
        mesh->vertices[index++] = glm::vec3(-v, -v, v);

        //Top
        mesh->vertices[index++] = glm::vec3(-v, v, -v);
        mesh->vertices[index++] = glm::vec3(-v, v, v);
        mesh->vertices[index++] = glm::vec3(v, v, -v);
        mesh->vertices[index++] = glm::vec3(v, v, -v);
        mesh->vertices[index++] = glm::vec3(-v, v, v);
        mesh->vertices[index++] = glm::vec3(v, v, v);

        //Front
        mesh->vertices[index++] = glm::vec3(-v, -v, v);
        mesh->vertices[index++] = glm::vec3(v, -v, v);
        mesh->vertices[index++] = glm::vec3(-v, v, v);
        mesh->vertices[index++] = glm::vec3(v, -v, v);
        mesh->vertices[index++] = glm::vec3(v, v, v);
        mesh->vertices[index++] = glm::vec3(-v, v, v);

        //Back
        mesh->vertices[index++] = glm::vec3(-v, -v, -v);
        mesh->vertices[index++] = glm::vec3(-v, v, -v);
        mesh->vertices[index++] = glm::vec3(v, -v, -v);
        mesh->vertices[index++] = glm::vec3(v, -v, -v);
        mesh->vertices[index++] = glm::vec3(-v, v, -v);
        mesh->vertices[index++] = glm::vec3(v, v, -v);

        //Left
        mesh->vertices[index++] = glm::vec3(-v, -v, v);
        mesh->vertices[index++] = glm::vec3(-v, v, -v);
        mesh->vertices[index++] = glm::vec3(-v, -v, -v);
        mesh->vertices[index++] = glm::vec3(-v, -v, v);
        mesh->vertices[index++] = glm::vec3(-v, v, v);
        mesh->vertices[index++] = glm::vec3(-v, v, -v);

        //Right
        mesh->vertices[index++] = glm::vec3(v, -v, v);
        mesh->vertices[index++] = glm::vec3(v, -v, -v);
        mesh->vertices[index++] = glm::vec3(v, v, -v);
        mesh->vertices[index++] = glm::vec3(v, -v, v);
        mesh->vertices[index++] = glm::vec3(v, v, -v);
        mesh->vertices[index++] = glm::vec3(v, v, v);

        index = 0;
        ///TEXTURE COORDINATE DATA
        mesh->textureCoordinates = new glm::vec2[mesh->numberOfVertices];

        float textureRepetition = textureRepetitionFactor <= 0.0f ? 1.0f : textureRepetitionFactor;

        //Bottom
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);

        //Top
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);

        //Front
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);

        //Back
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);

        //Left
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);

        //Right
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(textureRepetition, textureRepetition);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, 0.0f);
        mesh->textureCoordinates[index++] = glm::vec2(0.0f, textureRepetition);



        ///COLOR DATA
        mesh->colours = new glm::vec4[mesh->numberOfVertices];
        for (size_t i = 0; i < mesh->numberOfVertices; ++i)
        {
            mesh->colours[i] = Color::WHITE;
        }
        /* m->colours[0] = Color::Black();
        m->colours[1] = Color::Red();
        m->colours[2] = Color::Yellow();
        m->colours[3] = Color::Green();
        m->colours[4] = Color::White();
        m->colours[5] = Color::Blue();
        m->colours[6] = Color::Magenta();
        m->colours[7] = Color::Cyan();*/

        /*mesh->numberOfIndices = 36;
        mesh->indices = new GLuint[mesh->numberOfIndices];
        GLuint* id = mesh->indices;
        //bottom face
        *id++ = 0; 	*id++ = 5; 	*id++ = 4;
        *id++ = 5; 	*id++ = 0; 	*id++ = 1;

        //top face
        *id++ = 3; 	*id++ = 7; 	*id++ = 6;
        *id++ = 3; 	*id++ = 6; 	*id++ = 2;

        //front face
        *id++ = 7; 	*id++ = 4; 	*id++ = 6;
        *id++ = 6; 	*id++ = 4; 	*id++ = 5;

        //back face
        *id++ = 2; 	*id++ = 1; 	*id++ = 3;
        *id++ = 3; 	*id++ = 1; 	*id++ = 0;

        //left face
        *id++ = 3; 	*id++ = 0; 	*id++ = 7;
        *id++ = 7; 	*id++ = 0; 	*id++ = 4;

        //right face
        *id++ = 6; 	*id++ = 5; 	*id++ = 2;
        *id++ = 2; 	*id++ = 5; 	*id++ = 1;*/

        /*uint txtr = 0;
        mesh->textureCoordinates = new glm::vec2[24];

        mesh->textureCoordinates[0] = glm::vec2(0.f, 0.f);
        mesh->textureCoordinates[1] = glm::vec2(1.f, 0.f);
        mesh->textureCoordinates[2] = glm::vec2(0.f, 1.f);
        mesh->textureCoordinates[3] = glm::vec2(1.f, 1.f);*/

        mesh->GenerateNormals();

        //This is a manual version of the cube's normals
        /*mesh->normals = new glm::vec3[mesh->numberOfVertices];
        for (size_t i = 0; i < 6; ++i) mesh->normals[i]      = glm::vec3(0.f, -1.f, 0.f);
        for (size_t i = 0; i < 6; ++i) mesh->normals[6 + i]  = glm::vec3(0.f, 1.f, 0.f);;
        for (size_t i = 0; i < 6; ++i) mesh->normals[12 + i] = glm::vec3(0.f, 0.f, 1.f);
        for (size_t i = 0; i < 6; ++i) mesh->normals[18 + i] = glm::vec3(0.f, 0.f, -1.f);
        for (size_t i = 0; i < 6; ++i) mesh->normals[24 + i] = glm::vec3(-1.f, 0.f, 0.f);
        for (size_t i = 0; i < 6; ++i) mesh->normals[30 + i] = glm::vec3(1.f, 0.f, 0.f);*/

        mesh->BufferData();

        return mesh;
    }

    Mesh* MeshHelper::CreateHeightMap(const char* heigtmapFileName, float sizeX, float sizeZ, float maxHeight)
    {
        int width, height, channels;
        unsigned char *ht_map = SOIL_load_image(heigtmapFileName,
            &width, &height,
            &channels, SOIL_LOAD_L);

        if (ht_map == nullptr)
        {
            LogErrorF("SOIL loading error: %s", SOIL_last_result());
            LogErrorF("Couldn't load heightmap: %s", heigtmapFileName);
            return nullptr;
        }

        //TO-DO: Handle the case when the image loading fails

        Mesh* hMap = CreateSurface(width, height, sizeX, sizeZ);

        //`ht_map` contains unsigned chars that range from 0 to 255 in value.
        //This is a workaround to treat them as percentages instead.
        maxHeight /= 255.f;

        //TO-DO: We just spent time building the surface, there's no need
        //       to spend even more time visiting every vertex to modify it...
        size_t offset = 0;
        for (size_t x = 0; x < (unsigned)width; ++x)
        {
            for (size_t z = 0; z < (unsigned)height; ++z)
            {
                offset = (x * width) + z;
                hMap->vertices[offset] = glm::vec3(hMap->vertices[offset].x, maxHeight * ht_map[offset], hMap->vertices[offset].z);

                /*if (ht_map[offset] < 20) hMap->colours[offset] = Color::Blue();
                else if (ht_map[offset] < 204) hMap->colours[offset] = Color::Green();
                else hMap->colours[offset] = Color::White();*/
            }
        }
        SOIL_free_image_data(ht_map);
        hMap->GenerateNormals();

        hMap->BufferData();

        return hMap;
    }

    Mesh* MeshHelper::CreateSurface(size_t width, size_t height, float sizeX, float sizeZ)
    {
        Mesh* m = new Mesh();

        m->typeOfPrimitive = GL_TRIANGLES;

        m->numberOfVertices = width * height;
        m->vertices = new glm::vec3[m->numberOfVertices];
        m->textureCoordinates = new glm::vec2[m->numberOfVertices];
        m->colours = new glm::vec4[m->numberOfVertices];

        float textureX = 1.0f / sizeX;
        float textureZ = 1.0f / sizeZ;

        glm::vec3 originOffset = glm::vec3(width * sizeX * -0.5f, 0.f, height * sizeZ * -0.5f);

        //TO-DO: Center the surface to its origin, right now it's being created in the XZ plane.
        size_t offset = 0;
        for (size_t x = 0; x < width; ++x)
        {
            for (size_t z = 0; z < height; ++z)
            {
                offset = (x * width) + z;
                m->vertices[offset] = glm::vec3(x * sizeX, 0.f, z * sizeZ) + originOffset;
                m->colours[offset] = Color::WHITE;
                m->textureCoordinates[offset] = glm::vec2(x * textureX, z * textureZ);
            }
        }

        m->numberOfIndices = (width - 1) * (height - 1) * 6;
        m->indices = new GLuint[m->numberOfIndices];

        uint index = 0;

        for (size_t x = 0; x < width - 1; ++x)
        {
            for (size_t z = 0; z < height - 1; ++z)
            {
                int a = (x * width) + z;
                int b = ((x + 1) * width) + z;
                int c = ((x + 1) * width) + (z + 1);
                int d = (x * width) + (z + 1);

                m->indices[index++] = c;
                m->indices[index++] = b;
                m->indices[index++] = a;

                m->indices[index++] = a;
                m->indices[index++] = d;
                m->indices[index++] = c;
            }
        }

        /*for (size_t i = 0; i < m->numberOfVertices; ++i)
        {
        m->colours[i] = Color::White();
        }*/

        m->BufferData();

        return m;
    }

    Mesh* MeshHelper::CreateCoordinateSystem(float size)
    {
        Mesh* mesh = new Mesh();
        mesh->typeOfPrimitive = GL_LINES;

        mesh->numberOfVertices = 6;

        mesh->vertices = new glm::vec3[mesh->numberOfVertices];
        mesh->colours = new glm::vec4[mesh->numberOfVertices];

        //x axis arrow
        mesh->vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->vertices[1] = glm::vec3(size, 0.0f, 0.0f);

        mesh->colours[0] = Color::RED;
        mesh->colours[1] = Color::RED;

        //y axis
        mesh->vertices[2] = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->vertices[3] = glm::vec3(0.0f, size, 0.0f);

        mesh->colours[2] = Color::GREEN;
        mesh->colours[3] = Color::GREEN;

        //z axis
        mesh->vertices[4] = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->vertices[5] = glm::vec3(0.0f, 0.0f, size);

        mesh->colours[4] = Color::BLUE;
        mesh->colours[5] = Color::BLUE;

        mesh->BufferData();

        return mesh;
    }

    MutableMesh* MeshHelper::CreateTextMesh()
    {
        MutableMesh* m = new MutableMesh();

        m->typeOfPrimitive = GL_TRIANGLE_STRIP;
        m->typeOfDraw = GL_DYNAMIC_DRAW;

        float v = 1.0f;
        m->numberOfVertices = 4;
        m->vertices = new glm::vec3[m->numberOfVertices];
        m->vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
        m->vertices[1] = glm::vec3(0.0f, 0.0f, 0.0f);
        m->vertices[2] = glm::vec3(0.0f, 0.0f, 0.0f);
        m->vertices[3] = glm::vec3(0.0f, 0.0f, 0.0f);

        m->textureCoordinates = new glm::vec2[m->numberOfVertices];
        m->textureCoordinates[0] = glm::vec2(0.0f, 0.0f);
        m->textureCoordinates[1] = glm::vec2(1.0f, 0.0f);
        m->textureCoordinates[2] = glm::vec2(0.0f, 1.0f);
        m->textureCoordinates[3] = glm::vec2(1.0f, 1.0f);

        m->BufferData();

        return m;
    }
}

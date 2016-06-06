#include "Mesh.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files

#include "../Debugging/Debugging.h"

namespace Symphony
{
    Mesh::Mesh()
    {
        numberOfVertices    = 0;
        numberOfIndices     = 0;

        vertices            = nullptr;
        indices             = nullptr;
        colours             = nullptr;
        normals             = nullptr;
        tangents            = nullptr;
        textureCoordinates  = nullptr;
        
        typeOfPrimitive = GL_TRIANGLES;

        for (unsigned short i = 0; i < MAX_BUFFER; ++i)
        {
            vboID[i] = 0;
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

    //TO-DO: Could it be benefitial to cache the result of operations such as `numberOfVertices * sizeof(glm::vec3)`?
    void Mesh::BufferData()
    {
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        
        glGenBuffers(1, &vboID[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vboID[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_BUFFER);

        if (colours)
        {
            glGenBuffers(1, &vboID[COLOUR_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[COLOUR_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec4), colours, GL_STATIC_DRAW);

            glEnableVertexAttribArray(COLOUR_BUFFER);
            glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (textureCoordinates)
        {
            glGenBuffers(1, &vboID[TEXTURE_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[TEXTURE_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec2), textureCoordinates, GL_STATIC_DRAW);

            glEnableVertexAttribArray(TEXTURE_BUFFER);
            glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (indices)
        {
            glGenBuffers(1, &vboID[INDEX_BUFFER]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[INDEX_BUFFER]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
        }

        if (normals)
        {
            glGenBuffers(1, &vboID[NORMAL_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[NORMAL_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), normals, GL_STATIC_DRAW);

            glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(NORMAL_BUFFER);
        }
        
        if (tangents)
        {
            glGenBuffers(1, &vboID[TANGENT_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[TANGENT_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), tangents, GL_STATIC_DRAW); //texture.textureCoordinates

            glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(TANGENT_BUFFER);
        }

        glBindVertexArray(0);
    }

    void Mesh::Render()
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


    Mesh* Mesh::Triangle()
    {
        Mesh* mesh = new Mesh();

        mesh->typeOfPrimitive = GL_TRIANGLES;

        mesh->numberOfVertices = 3;
        mesh->vertices = new glm::vec3[mesh->numberOfVertices];
        mesh->vertices[0] = glm::vec3(-1, -1, 0);
        mesh->vertices[1] = glm::vec3(1, -1, 0);
        mesh->vertices[2] = glm::vec3(0, 1, 0);

        mesh->colours = new glm::vec4[mesh->numberOfVertices];
        mesh->colours[0] = Color::Red();    //Color::White();
        mesh->colours[1] = Color::Green();  //Color::White();
        mesh->colours[2] = Color::Blue();   //Color::White();

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

    Mesh* Mesh::Quad()
    {
        Mesh* mesh = new Mesh();
        mesh->typeOfPrimitive = GL_TRIANGLE_STRIP;

        mesh->numberOfVertices = 4;
        mesh->vertices = new glm::vec3[mesh->numberOfVertices];
        mesh->vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
        mesh->vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
        mesh->vertices[2] = glm::vec3(-1.0f, 1.0f, 0.0f);
        mesh->vertices[3] = glm::vec3(1.0f, 1.0f, 0.0f);
        
        mesh->numberOfIndices = 4;
        mesh->indices = new GLuint[mesh->numberOfIndices];
        mesh->indices[0] = 0;
        mesh->indices[1] = 1;
        mesh->indices[2] = 2;
        mesh->indices[3] = 3;

        mesh->colours = new glm::vec4[mesh->numberOfVertices];
        mesh->colours[0] = Color::Red();
        mesh->colours[1] = Color::Green();
        mesh->colours[2] = Color::Blue();
        mesh->colours[3] = Color::Yellow();
        
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
        
        //TO-DO: For some reason, the texture coordinates were swapped in the Y axis?
        mesh->textureCoordinates = new glm::vec2[mesh->numberOfVertices];
        mesh->textureCoordinates[0] = glm::vec2(0.f, 1.f);
        mesh->textureCoordinates[1] = glm::vec2(1.f, 1.f);
        mesh->textureCoordinates[2] = glm::vec2(0.f, 0.f);
        mesh->textureCoordinates[3] = glm::vec2(1.f, 0.f);
        
        mesh->BufferData();

        return mesh;
    }

    Mesh * Mesh::CoordinateSystem(float size)
    {
        Mesh* mesh = new Mesh();
        mesh->typeOfPrimitive = GL_LINES;
        
        mesh->numberOfVertices = 6;

        mesh->vertices = new glm::vec3[mesh->numberOfVertices];
        mesh->colours = new glm::vec4[mesh->numberOfVertices];
        
        //x axis arrow
        mesh->vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->vertices[1] = glm::vec3(size, 0.0f, 0.0f);

        mesh->colours[0] = Color::Red();
        mesh->colours[1] = Color::Red();

        //y axis
        mesh->vertices[2] = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->vertices[3] = glm::vec3(0.0f, size, 0.0f);

        mesh->colours[2] = Color::Green();
        mesh->colours[3] = Color::Green();

        //z axis
        mesh->vertices[4] = glm::vec3(0.0f, 0.0f, 0.0f);
        mesh->vertices[5] = glm::vec3(0.0f, 0.0f, size);

        mesh->colours[4] = Color::Blue();
        mesh->colours[5] = Color::Blue();

        mesh->BufferData();
        
        return mesh;
    }
}


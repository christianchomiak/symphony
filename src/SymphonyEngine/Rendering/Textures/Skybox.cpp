#include "Skybox.h"


namespace Symphony
{
    /*Skybox::Skybox()
    {
        skyboxID = 0;
        mesh = nullptr;
        shader = nullptr;
    }*/
    
    Skybox::Skybox()
        : skyboxID(0), mesh(nullptr), shader(nullptr)
    {
    }

    Skybox::Skybox(GLuint id, Mesh* mesh, Shader* shader)
        : skyboxID(id), mesh(mesh), shader(shader)
    {
    }

    Skybox::~Skybox()
    {
        //Delete the skybox texture object
        //glDeleteTextures(1, &skyboxID);
        
        //delete mesh;
        //delete shader;
    }
}

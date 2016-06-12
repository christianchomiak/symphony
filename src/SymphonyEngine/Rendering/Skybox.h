#pragma once

#define GLEW_STATIC
#include <GLEW/GL/glew.h>
#include "Mesh.h"
#include "Shader.h"

namespace Symphony
{
    struct Skybox
    {
        friend class Camera;
        friend class TextureManager;

    public:
        Skybox();
        Skybox(GLuint id, Mesh* mesh, Shader* shader);
        ~Skybox();
        bool IsValidSkybox() const;

    protected:
        unsigned int skyboxID;
        Mesh* mesh;
        Shader* shader;
    };

    inline bool Skybox::IsValidSkybox() const
    {
        return skyboxID > 0 && mesh && shader;
    }
}
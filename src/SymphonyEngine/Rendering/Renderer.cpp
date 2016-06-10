#include "Renderer.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files


//Symphony::Camera* Symphony::Renderer::currentCamera = nullptr;

void Symphony::Renderer::ProcessTexture(const Texture& texture) const
{
    glBindTexture(GL_TEXTURE_2D, texture.ID());

    GLuint action;

    //WRAPPING
    switch (texture.wrapping)
    {
    case Texture::WrappingType::REPEAT:
        action = GL_REPEAT;
        break;
    case Texture::WrappingType::MIRRORED_REPEAT:
        action = GL_MIRRORED_REPEAT;
        break;
    case Texture::WrappingType::CLAMP:
        action = GL_CLAMP;
        break;
    case Texture::WrappingType::CLAMP_TO_EDGE:
        action = GL_CLAMP_TO_EDGE;
        break;
    case Texture::WrappingType::CLAMP_TO_BORDER:
        action = GL_CLAMP_TO_BORDER;
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, action);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, action);

    //FILTERING
    switch (texture.filter)
    {
    case Texture::FilteringType::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case Texture::FilteringType::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case Texture::FilteringType::TRILINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }    

    //We can't unbind the texture as it'll be used during the rendering process
    //glBindTexture(GL_TEXTURE_2D, 0);
}

#include "SimpleRenderer.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

SimpleRenderer::SimpleRenderer()
{
    m = Mesh::Quad();
    s = Shader::GetShader("UNLIT_COLOR");
}

SimpleRenderer::~SimpleRenderer()
{
    delete m;
}

void SimpleRenderer::Render()
{
    glm::mat4  P = glm::mat4(1);
    glm::mat4 MV = glm::mat4(1);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!s)
    {
        std::cout << "NO SHADER FOUND" << std::endl;
        return;
    }
    Shader& ss = *s;

    ss.Use();
    glUniformMatrix4fv(ss("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));

    m->Render();

    s->Release();
}
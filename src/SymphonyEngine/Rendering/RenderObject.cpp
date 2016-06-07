#include "RenderObject.h"

namespace Symphony
{
    RenderObject::RenderObject()
        : mesh(nullptr), shader(nullptr)
    {
    }
    
    RenderObject::RenderObject(Mesh* m, Texture t, Shader* s)
        : mesh(m), texture(t), shader(s)
    {
    }

    RenderObject::RenderObject(Mesh* m, Shader* s)
        : mesh(m), shader(s)
    {
    }

    RenderObject::~RenderObject()
    {
        delete mesh;
    }

}

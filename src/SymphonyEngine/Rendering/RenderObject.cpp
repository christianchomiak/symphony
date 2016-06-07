#include "RenderObject.h"

namespace Symphony
{
    RenderObject::RenderObject()
        : mesh(nullptr), shader(nullptr), boundingRadius(FLT_MAX)
    {
    }
    
    RenderObject::RenderObject(Mesh* m, Texture t, Shader* s)
        : mesh(m), texture(t), shader(s), boundingRadius(FLT_MAX)
    {
    }

    RenderObject::RenderObject(Mesh* m, Shader* s)
        : mesh(m), shader(s), boundingRadius(FLT_MAX)
    {
    }

    RenderObject::~RenderObject()
    {
        delete mesh;
    }

}

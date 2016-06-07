#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

namespace Symphony
{
    //Subsystem of GameObject, in charge of controlling everything related
    //to its rendering properties (mesh, texture, etc.). The existence, or shape, 
    //of this class may vary in the future.
    class RenderObject
    {
        friend class GameObject;
    public:
        RenderObject();
        RenderObject(Mesh*, Texture, Shader*);
        RenderObject(Mesh*, Shader*);

        void SetMesh(Mesh*);
        void SetTexture(const Texture& t);
        void SetShader(Shader* s);

        Mesh* GetMesh() const;
        const Texture& GetTexture() const;
        Shader* GetShader() const;

        bool OkToRender() const;
        
        float GetBoundingRadius() const;
        void SetBoundingRadius(float);

        //static bool CompareByCameraDistance(RenderObject*, RenderObject*);

    protected:
        Mesh* mesh;
        Texture texture;    //TO-DO: Textures should be part of a material, together with the shader reference
        Shader* shader;

        //TO-DO: this value should be calculated using the proportions from the mesh
        float boundingRadius;

    protected:
        ~RenderObject();
    };
    
    inline void RenderObject::SetMesh(Mesh *m)
    {
        mesh = m;
    }

    inline void RenderObject::SetTexture(const Texture & t)
    {
        texture.id = t.id;
        texture.wrapping = t.wrapping;
        texture.filter = t.filter;
    }

    inline void RenderObject::SetShader(Shader * s)
    {
        shader = s;
    }

    inline Mesh* RenderObject::GetMesh() const
    {
        return mesh;
    }

    inline const Texture& RenderObject::GetTexture() const
    {
        return texture;
    }

    inline Shader* RenderObject::GetShader() const
    {
        return shader;
    }

    inline bool RenderObject::OkToRender() const
    {
        return mesh != nullptr && shader != nullptr;
    }

    inline float RenderObject::GetBoundingRadius() const
    {
        return boundingRadius;
    }
    
    inline void RenderObject::SetBoundingRadius(float br)
    {
        boundingRadius = br;
    }
}
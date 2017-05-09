#pragma once

#include "Mesh/Mesh.h"
#include "Textures/Texture.h"
#include "Shader.h"
#include "Material.h"

#include "../Macros/QAMacros.h"

namespace Symphony
{
    //Subsystem of GameObject, in charge of controlling everything related
    //to its rendering properties (mesh, texture, etc.). The existence, or shape, 
    //of this class may vary in the future.
    class RenderObject
    {
        friend class GameObject;
    public:
        Material material;

        RenderObject();
        RenderObject(Mesh*, Texture, Shader*);
        RenderObject(Mesh*, Shader*);

        void SetMesh(Mesh*);
        void SetTexture(const Texture& t);
        void SetShader(Shader* s);
        
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        Mesh* GetMesh() const;
        Shader* GetShader() const;
        const Texture& GetTexture() const;

        bool OkToRender() const;
        
        float GetBoundingRadius() const;
        void SetBoundingRadius(float);

        //static bool CompareByCameraDistance(RenderObject*, RenderObject*);

    protected:
        Mesh*   mesh;
        Shader* shader;
        Texture texture;    //TO-DO: Textures should be part of a material, together with the shader reference

        //TO-DO: this value should be calculated using the proportions from the mesh and the scale of the object
        float boundingRadius;

    protected:
        ~RenderObject();
    };
    
    inline void RenderObject::SetMesh(Mesh* m)
    {
        NULL_POINTER_WARNING(m, return);
        mesh = m;
    }

    inline void RenderObject::SetTexture(const Texture& t)
    {
        texture.CopyValuesFromTexture(t);
    }

    inline void RenderObject::SetShader(Shader* s)
    {
        NULL_POINTER_WARNING(s, return);
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
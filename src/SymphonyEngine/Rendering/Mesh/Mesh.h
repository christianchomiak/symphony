#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <SymphonyGlobal.h>
#include <Rendering/Color.h> //Already includes <glm/vec4.hpp>

namespace Symphony
{
    enum MeshBuffer 
    {
        VERTEX_BUFFER,      //layout(location = 0)
        COLOUR_BUFFER,      //layout(location = 1)
        TEXTURE_BUFFER,     //layout(location = 2)
        NORMAL_BUFFER,      //layout(location = 3)
        TANGENT_BUFFER,     //layout(location = 4)
        INDEX_BUFFER,       //layout(location = 5)
        MAX_BUFFER
    };
    
    //TO-DO: Provide means to have pooled meshes and individual meshes (whose lifetimes are determined by the programmer)
    class Mesh
    {
    public:
        friend class MeshHelper;

        //TODO: This property should be independent from the mesh.
        //      The RenderObject should have a pointer to the mesh (in order to save memory!)
        //      and have a MeshProperties (tentative name) holding instance-specific properties.
        bool allowFaceCulling;

        ~Mesh();

        void Render() const;
        void BufferData() const;
        bool IsFaceCullingEnabled() const;
        void EnableFaceCulling();
        void DisableFaceCulling();
        void SetFaceCullingStatus(bool cullEnabled);

        uint GetVBO() const;
        uint GetVAO() const;

        //bool UpdateVertices(glm::vec3* newVertexData, int numberOfNewVertexData);

    protected:
        mutable uint vaoID;
        mutable uint vboID[MAX_BUFFER];
        uint typeOfPrimitive;
        uint typeOfDraw;

        uint numberOfVertices,
                     numberOfIndices;

        uint* indices;
        glm::vec3 *vertices,
                  *normals,
                  *tangents;
        glm::vec2 *textureCoordinates;
        glm::vec4 *colours;

    protected:
        Mesh();

        void GenerateNormals();
    };


    inline uint Mesh::GetVBO() const
    {
        return vboID[VERTEX_BUFFER];
    }

    inline uint Mesh::GetVAO() const
    {
        return vaoID;
    }

    inline bool Mesh::IsFaceCullingEnabled() const
    {
        return allowFaceCulling;
    }

    inline void Mesh::EnableFaceCulling()
    {
        allowFaceCulling = true;
    }

    inline void Mesh::DisableFaceCulling()
    {
        allowFaceCulling = false;
    }

    inline void Mesh::SetFaceCullingStatus(bool cullEnabled)
    {
        allowFaceCulling = cullEnabled;
    }
}
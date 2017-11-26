#pragma once

#include "Mesh.h"
#include "MutableMesh.h"

#include <Macros/ClassMacros.h>

namespace Symphony
{
    class MeshHelper
    {
    public:
        static Mesh* CreateTriangle();
        static Mesh* CreateQuad();
        static Mesh* CreateCube();
        static Mesh* CreateHeightMap(const char* heigtmapFileName, float sizeX, float sizeZ, float maxHeight = 1.f);
        static Mesh* CreateSurface(size_t width, size_t height, float sizeX, float sizeZ);
        static Mesh* CreateCoordinateSystem(float size = 1.f);
        static MutableMesh* CreateTextMesh();

        NO_DEFAULT_CONSTRUCTORS(MeshHelper)
        NO_DESTRUCTOR(MeshHelper)
    };
}
#pragma once

#include <vector>
#include "../Engine/Camera/Camera.h"

namespace Symphony
{
    class Renderer
    {
    public:
        virtual ~Renderer() {};
        virtual void Render(const std::vector<Camera*>& cameras, const GameObject* sceneRoot) = 0;
        void ProcessTexture(const Texture& t) const;
    };
}
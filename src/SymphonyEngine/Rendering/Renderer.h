#pragma once

#include <vector>
#include "../Scene/Scene.h"

namespace Symphony
{
    class Renderer
    {
    public:
        virtual ~Renderer() {};
        virtual void Render(const GameObject* sceneRoot, const std::vector<Camera*>& cameras, const std::vector<Light*>& lights) = 0;
        void ProcessTexture(const Texture& t) const;
    };
}
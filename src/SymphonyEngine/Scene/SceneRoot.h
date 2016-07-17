#pragma once

#include "GameObject.h"

namespace Symphony
{
    class SceneRoot final : public GameObject
    {
        friend class Scene;
    public:
        SceneRoot(const SceneRoot&) = delete;
        SceneRoot& operator=(const SceneRoot&) = delete;
    protected:
        SceneRoot() {}
        virtual ~SceneRoot() {}
    };
}
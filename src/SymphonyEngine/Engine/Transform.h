#pragma once

namespace Symphony
{
    class GameObject;

    class Transform
    {
    public:
        Transform();
        ~Transform();

        GameObject* parent;
    };
}
#pragma once

#include "Text.h"
#include "../GameObject.h"

namespace Symphony
{
    class Text2D : public GameObject
    {
    public:
        Text2D();
        Text2D(const Text&);
        Text2D(const std::string&);
        virtual ~Text2D();
        Text text;
    };
}
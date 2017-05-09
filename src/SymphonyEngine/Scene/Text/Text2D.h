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
        explicit Text2D(Font* font, const Text&);
        explicit Text2D(Font* font, const std::string&);
        virtual ~Text2D();
        
        void RenderBackground() const;
        void Render() const;

        inline Text& GetText()
        {
            return text;
        }

        Text text;
    };
}
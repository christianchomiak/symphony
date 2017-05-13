#pragma once

#include "Text.h"
#include "../GameObject.h"

namespace Symphony
{
    class Text2D : public GameObject
    {
    public:
        Text2D(char* objName = nullptr);
        Text2D(const Text&, char* objName = nullptr);
        explicit Text2D(Font* font, const std::string& content, char* objName = nullptr);
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
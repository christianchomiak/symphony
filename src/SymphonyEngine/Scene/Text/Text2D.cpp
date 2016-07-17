#include "Text2D.h"

namespace Symphony
{
    Text2D::Text2D()
    {
    }

    Text2D::Text2D(const Text& t)
        : text(t)
    {
    }
    
    Text2D::Text2D(const std::string& content)
        : text(Text(content))
    {
    }

    Text2D::~Text2D()
    {
    }
}
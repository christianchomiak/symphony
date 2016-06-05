#pragma once

namespace Symphony
{
    struct Screen
    {
        friend class Window;
    public:
        static float AspectRatio();
        static int Width();
        static int Height();

    protected:
        static int width, height;
    };
    
    inline int Screen::Width()
    {
        return width;
    }

    inline int Screen::Height()
    {
        return height;
    }

    inline float Screen::AspectRatio()
    {
        //TO-DO: floats are imprecise, use a better suited check
        if (height == 0.f) return 0.f;

        return (float)width / (float)height;
    }
}
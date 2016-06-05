#pragma once

#include "../../Window/Screen.h"

namespace Symphony
{
    struct ViewPort
    {
    public:
        int startXPosition;
        int startYPosition;
        int width;
        int height;

        ViewPort() : ViewPort(ViewPort::FullScreen())
        {
        }

        ViewPort(int x, int y, int w, int h)
            : startXPosition(x), startYPosition(y), width(w), height(h)
        {
        }

        ViewPort(const ViewPort& vp) : ViewPort(vp.startXPosition, vp.startYPosition, vp.width, vp.height)
        {
        }

        float AspectRatio() const;

    public:
        static ViewPort FullScreen();
    };

    inline float ViewPort::AspectRatio() const {
        return (float)width / (float)height;
    }

    inline ViewPort ViewPort::FullScreen()
    {
        int w = Screen::Width();
        int h = Screen::Height();
        int x = 0;
        int y = 0;
        return ViewPort(x, y, w, h);
    }
}
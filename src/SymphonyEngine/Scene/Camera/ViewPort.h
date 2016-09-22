#pragma once

#include "../../Window/Screen.h"

namespace Symphony
{
    struct ViewPort
    {
    protected:
        int startXPosition;
        int startYPosition;
        int width;
        int height;
        float aspectRatio;

    public:
        ViewPort() : ViewPort(ViewPort::FullScreen())
        {
        }

        ViewPort(int x, int y, int w, int h)
            : startXPosition(x), startYPosition(y), width(w), height(h)
        {
            aspectRatio = (float)width / (float)height;
        }

        ViewPort(const ViewPort& vp)
            : ViewPort(vp.startXPosition, vp.startYPosition, vp.width, vp.height)
        {
        }

        float AspectRatio() const;

    public:
        static ViewPort FullScreen();
    };

    inline float ViewPort::AspectRatio() const
    {
        return aspectRatio;
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
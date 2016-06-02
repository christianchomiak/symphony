#pragma once

#include <GLFW/glfw3.h>

namespace Symphony
{
    class Window
    {
    public:
        Window(const char* name, int width, int height);
        ~Window();

        bool Initialise();
        void Clear() const;
        void Update();
        bool Closed() const;

        void ChangeName(const char* newName);

        inline const int Width() const { return width; }
        inline const int Height() const { return height; }

        static bool windowResized;

    protected:
        const char* name;
        int width, height;
        GLFWwindow* window;

        void HandleResize();
    };
}
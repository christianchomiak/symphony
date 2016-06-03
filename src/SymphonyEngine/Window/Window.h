#pragma once

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files
#include <GLFW/glfw3.h>

namespace Symphony
{
    class Window
    {
    public:
        enum CursorMode { DISABLED, NORMAL, HIDDEN };

        Window(const char* name, int width, int height);
        ~Window();

        bool Initialise();
        void Clear() const;
        void SwapBuffers() const;
        void Update();
        bool Closed() const;

        void ChangeName(const char* newName);
        void OutputRenderingInfo() const;

        void ChangeCursorMode(CursorMode newMode);

        inline const int Width() const { return width; }
        inline const int Height() const { return height; }

        void HandleResize();
        static void glfwErrorCallback(int error, const char* description);

    protected:
        const char* name;
        int width, height;
        CursorMode cursorMode;
        GLFWwindow* window;
    };
}
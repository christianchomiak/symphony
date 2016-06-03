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

        struct WindowProperties
        {
            const char* title;

            //TO-DO: Provide alterate means of specifying that the width and height should be queried from the monitor
            int width, height;

            bool fullscreen;
            
            //Windowed Mode
            bool resizeable,
                decorated,
                maximised;

            bool switchableToOtherModes;

            Window::CursorMode cursorMode;

            WindowProperties()
            : WindowProperties("Symphony Window", 800, 600, false, true, true, false, false, Window::CursorMode::NORMAL)
            {
            }

            WindowProperties(WindowProperties& other)
                : WindowProperties(other.title, other.width, other.height, other.fullscreen, other.resizeable, 
                                   other.decorated, other.maximised, other.switchableToOtherModes, other.cursorMode)
            {
            }
            
            WindowProperties(const char* title, int width, int height, bool fullscreen, bool resizeable, bool decorated,
                             bool maximised, bool switchableToOtherModes, Window::CursorMode cursorMode)
            {
                this->title = title;
                this->width = width;
                this->height = height;
                this->fullscreen = fullscreen;
                this->resizeable = resizeable;
                this->decorated = decorated;
                this->maximised = maximised;
                this->switchableToOtherModes = switchableToOtherModes;
                this->cursorMode = cursorMode;
            }
        };
        
        Window() = delete;
        Window(Window&) = delete;
        Window(WindowProperties& properties);
        ~Window();
        
        bool Initialise();
        void Clear() const;
        void SwapBuffers() const;
        void Update();
        bool Closed() const;
        
        void SetTitle(const char* newName);
        void OutputRenderingInfo() const;

        void ChangeCursorMode(CursorMode newMode);

        void ChangeMode();

        inline const int Width() const { return properties.width; }
        inline const int Height() const { return properties.height; }

        void HandleResize();
        static void glfwErrorCallback(int error, const char* description);

    protected:
        WindowProperties properties;
        GLFWwindow* window;
        
        Window(const char* title, int width, int height, bool resizeable, bool decorated, bool maximised, bool switchableToFullscreen);
        Window(const char* title, int width, int height, bool switchableToWindowed);
    };
}
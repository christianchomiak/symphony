#pragma once

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files
#include <GLFW/glfw3.h>

#include <string>

#include "../Macros/ClassMacros.h"

namespace Symphony
{
    class Window
    {
    public:
        enum CursorMode 
        {
            DISABLED, //Cursor not visible neither inside nor outside the window
            VISIBLE,  //Cursor visible inside the window
            HIDDEN    //Cursor visible outside but not inside the window
        };

        struct WindowProperties
        {
            std::string title;

            //TO-DO: Provide alterate means of specifying that the width and height should be queried from the monitor
            unsigned int width, height;

            bool fullscreen;
            
            //Windowed Mode
            bool resizeable,
                 borderless,
                 maximised;

            bool switchableToOtherModes;

            Window::CursorMode cursorMode;

            WindowProperties()
                : WindowProperties("", 800, 600, false, true, false, false, false, Window::CursorMode::VISIBLE)
            {
            }

            WindowProperties(WindowProperties& other)
                : WindowProperties(other.title, other.width, other.height, other.fullscreen, other.resizeable, 
                                   other.borderless, other.maximised, other.switchableToOtherModes, other.cursorMode)
            {
            }
            
            WindowProperties(const std::string& title, unsigned int width, unsigned int height,
                             bool fullscreen, bool resizeable, bool decorated, bool maximised,
                             bool switchableToOtherModes, Window::CursorMode cursorMode)
                : title(title), width(width), height(height), fullscreen(fullscreen),
                  resizeable(resizeable), borderless(decorated), maximised(maximised),
                  switchableToOtherModes(switchableToOtherModes), cursorMode(cursorMode)
            {
            }

            static WindowProperties LoadFromFile(const char* filename);
        };
        
        NO_DEFAULT_CONSTRUCTORS(Window)
        Window(WindowProperties& properties);
        ~Window();
        
        bool Initialise();
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

        //TO-DO: Should this be in a helper class?
        static bool GetMonitorResolution(int& w, int& h);

    protected:
        WindowProperties properties;
        GLFWwindow* window;
        
        Window(const char* title, int width, int height, bool resizeable, bool borderless, bool maximised, bool switchableToFullscreen);
        Window(const char* title, int width, int height, bool switchableToWindowed);
    };
}
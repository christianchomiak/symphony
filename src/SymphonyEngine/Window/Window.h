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
        public:
            std::string title;

            //TO-DO: Provide alterate means of specifying that the width and height should be queried from the monitor
            unsigned int width, height;
            unsigned int frameBufferWidth, frameBufferHeight;

            static const unsigned int MAX_NUMBER_OF_ICONS = 2;
            std::string iconsPaths[MAX_NUMBER_OF_ICONS];

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

            WindowProperties(const WindowProperties& other)
                : WindowProperties(other.title, other.width, other.height, other.fullscreen, other.resizeable, 
                                   other.borderless, other.maximised, other.switchableToOtherModes, other.cursorMode,
                                   other.iconsPaths[0].c_str(), other.iconsPaths[1].c_str())
            {
            }
            
            WindowProperties(const std::string& title, unsigned int width, unsigned int height,
                             bool fullscreen, bool resizeable, bool decorated, bool maximised,
                             bool switchableToOtherModes, Window::CursorMode cursorMode,
                             const char* bigIconPath = nullptr, const char* smallIconPath = nullptr )
                : title(title), width(width), height(height), fullscreen(fullscreen),
                  resizeable(resizeable), borderless(decorated), maximised(maximised),
                  switchableToOtherModes(switchableToOtherModes), cursorMode(cursorMode),
                  frameBufferWidth(width), frameBufferHeight(height),
                  iconsPaths{ bigIconPath ? bigIconPath : "", smallIconPath ? smallIconPath : "" }
            {
            }

            static WindowProperties CreateFromFile(const char* filename);
        };
        
        NO_DEFAULT_CONSTRUCTORS(Window)
        Window(const WindowProperties& properties);
        ~Window();
        
        bool Initialise();
        void SwapBuffers() const;
        void Update();
        bool Closed() const;
        
        void SetTitle(const char* newName);
        void OutputRenderingInfo() const;

        void ChangeCursorMode(CursorMode newMode);

        void ChangeMode();

        bool IsFocused() const;

        inline const WindowProperties& GetDefaultProperties() const
        {
            return defaultProperties;
        }

        inline int WindowWidth() const  { return properties.width;  }
        inline int WindowHeight() const { return properties.height; }

        inline int FrameBufferWidth() const  { return properties.frameBufferWidth;  }
        inline int FrameBufferHeight() const { return properties.frameBufferHeight; }

        void HandleResize();
        static void glfwErrorCallback(int error, const char* description);

        //TO-DO: Should this be in a helper class?
        static bool GetMonitorResolution(int& w, int& h);

    protected:
        WindowProperties properties;
        WindowProperties defaultProperties;
        GLFWwindow* window;
        
        Window(const char* title, int width, int height, bool resizeable, bool borderless, bool maximised, bool switchableToFullscreen);
        Window(const char* title, int width, int height, bool switchableToWindowed);
    };
}
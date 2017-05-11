#include "Window.h"

#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

//#include <imgui/imgui.h>

#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"
#include "../IO/DataReader.h"

#include "../UI/imgui/ImGuiManager.h"

#include "Screen.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    Symphony::Window* w = static_cast<Symphony::Window*>(glfwGetWindowUserPointer(window));
    w->HandleResize();
}

namespace Symphony
{
    Window::Window(const char* title, int width, int height, bool resizeable, bool borderless, bool maximised, bool switchableToFullscreen)
        : properties(title, width, height, false, resizeable, borderless, maximised, switchableToFullscreen, CursorMode::VISIBLE)
    {
        window = nullptr;
    }
    
    Window::Window(const char* title, int width, int height, bool switchableToWindowed)
        : properties(title, width, height, true, false, false, false, false, CursorMode::VISIBLE)
    {
        window = nullptr;
    }

    Window::Window(const WindowProperties& initialProperties)
        : properties(initialProperties), defaultProperties(initialProperties)
    {
        window = nullptr;
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
    }

    bool Window::Initialise()
    {
        /* Initialize the library */
        if (!glfwInit())
        {
            Debug::LogError("Failed to initialise GLFW");
            return false;
        }

        glfwSetErrorCallback(Window::glfwErrorCallback);

        //TO-DO: Setting a minimum OpenGL context seems to break the basic
        //triangle rendering used so far during development. Test again this
        //with an actual OpenGL application with proper usage of the OpenGL API

        //We suggest GLFW to create an OpenGL context using v3.3, at least
        //If the required minimum version is not supported on the machine, context (and window) creation fails.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        if (properties.fullscreen)
        {
            window = glfwCreateWindow(properties.frameBufferWidth, properties.frameBufferHeight, properties.title.c_str(), glfwGetPrimaryMonitor(), NULL);
        }
        else
        {
            glfwWindowHint(GLFW_RESIZABLE, properties.resizeable ? GL_TRUE : GL_FALSE);
            glfwWindowHint(GLFW_DECORATED, properties.borderless ? GL_FALSE : GL_TRUE);
            glfwWindowHint(GLFW_MAXIMIZED, properties.maximised  ? GL_TRUE : GL_FALSE);
            
            window = glfwCreateWindow(properties.frameBufferWidth, properties.frameBufferHeight, properties.title.c_str(), NULL, NULL);
        }

        if (!window)
        {
            Debug::LogError("Failed to initialise window");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        glfwSetWindowSizeCallback(window, WindowResizeCallback);
        glfwSetKeyCallback(window, InputManager::KeyboardKeyCallback);
        glfwSetMouseButtonCallback(window, InputManager::MouseButtonCallback);
        glfwSetCursorPosCallback(window, InputManager::MousePositionCallback);
        glfwSetJoystickCallback(InputManager::GamePadStatusCallback);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            Debug::LogError("Could not initialise GLEW!");
            return false;
        }
        
#ifdef IMGUI_API

#ifdef _WIN32
        ImGuiManager::Init(glfwGetWin32Window(window));
#endif

        glfwSetCharCallback(window, InputManager::ImGui_ImplGlfwGL3_CharCallback);
#endif

        HandleResize();
        //glViewport(0, 0, width, height);
        OutputRenderingInfo();
        
        ChangeCursorMode(properties.cursorMode);
        
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        if (!properties.fullscreen && !properties.maximised)
        {
            glfwSetWindowPos(window, (mode->width - properties.frameBufferWidth) / 2, (mode->height - properties.frameBufferHeight) / 2);
        }

        //TO-DO: Set the window's icon
        /*int width, height, channels;
        GLFWimage* icon = new GLFWimage();
        icon->pixels = SOIL_load_image
        (
        "../../icon.png",
        &width, &height, &channels,
        SOIL_LOAD_AUTO
        );
        icon->width = width;
        icon->height = height;
        glfwSetWindowIcon(window, 1, icon);*/

        return true;
    }

    void Window::SwapBuffers() const
    {
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    void Window::Update()
    {
        /* Poll for and process events */
        glfwPollEvents();
    }

    bool Window::Closed() const
    {
        return glfwWindowShouldClose(window) == 1;
    }

    void Window::SetTitle(const char* newName)
    {
        properties.title = newName;
        glfwSetWindowTitle(window, newName);
    }
    
    //TO-DO: Camera viewports should be updated whenever the window changes size
    void Window::HandleResize()
    {
        //glfwGetWindowSize(window, &width, &height);

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);

        properties.frameBufferWidth  = w;
        properties.frameBufferHeight = h;
        
        Screen::width  = properties.frameBufferWidth;
        Screen::height = properties.frameBufferHeight;

        glfwGetWindowSize(window, &w, &h);
        properties.width  = w;
        properties.height = h;
    }
    
    void Window::OutputRenderingInfo() const
    {
        std::cout << "Using GLEW "  << glewGetString(GLEW_VERSION)  << std::endl;
        std::cout << "Vendor: "     << glGetString(GL_VENDOR)       << std::endl;
        std::cout << "Renderer: "   << glGetString(GL_RENDERER)     << std::endl;
        std::cout << "Version: "    << glGetString(GL_VERSION)      << std::endl;
        std::cout << "GLSL: "       << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        Debug::LogF("Running against GLFW %i.%i.%i\n", major, minor, revision);
    }

    void Window::ChangeCursorMode(CursorMode newMode)
    {
        properties.cursorMode = newMode;

        switch (properties.cursorMode)
        {
        case CursorMode::DISABLED:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        case CursorMode::VISIBLE:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case CursorMode::HIDDEN:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;
        default:
            Debug::LogWarning("Trying to set the cursor of the window in an unavailable state.");
            break;
        }
    }

    void Window::ChangeMode()
    {
        if (!properties.switchableToOtherModes) return;

        properties.fullscreen = !properties.fullscreen;
        
        if (properties.fullscreen)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, properties.frameBufferWidth, properties.frameBufferHeight, GLFW_DONT_CARE);
            // mode->width, mode->height, GLFW_DONT_CARE);// mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(window, NULL, 0, 0, properties.frameBufferWidth, properties.frameBufferHeight, GLFW_DONT_CARE);
        }
        
        HandleResize();
    }

    bool Window::IsFocused() const
    {
        return glfwGetWindowAttrib(window, GLFW_FOCUSED);
    }

    void Window::glfwErrorCallback(int error, const char* description)
    {
        fprintf(stderr, "Error %d: %s\n", error, description);
    }

    bool Window::GetMonitorResolution(int & w, int & h)
    {
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        
        if (mode)
        {
            w = mode->width;
            h = mode->height;
            return true;
        }
        Debug::LogError("Could not access video mode of primary monitor");
        return false;
    }

    Window::WindowProperties Window::WindowProperties::CreateFromFile(const char* filename)
    {
        WindowProperties wProperties;
        
        if (filename == nullptr)
        {
            Debug::LogError("No filename was specified, default window properties will be used");
            return wProperties;
        }

        tinyxml2::XMLDocument doc;

        if (!ValidateXmlLoading(filename, doc.LoadFile(filename)))
        {
            Debug::LogError("Default window properties will be used");
            return wProperties;
        }

        tinyxml2::XMLElement* windowData = doc.FirstChildElement("SymphonyConfigData")->FirstChildElement("WindowData");

        if (!windowData)
        {
            Debug::LogErrorF("Could not find WindowData properties in \"%s\", default window properties will be used", filename);
            return wProperties;
        }

        const char* windowTitle = GetTextFromXmlElement(windowData, "Title");
        if (windowTitle == nullptr)
        {
            Debug::LogErrorF("Could not find windowTitle property in  \"%s\"", filename);
        }
        else
        {
            wProperties.title = windowTitle;
        }

        ReadFromXmlElement(windowData, "Borderless", wProperties.borderless);
        ReadFromXmlElement(windowData, "Fullscreen", wProperties.fullscreen);
        ReadFromXmlElement(windowData, "Maximised", wProperties.maximised);
        ReadFromXmlElement(windowData, "Resizeable", wProperties.resizeable);
        ReadFromXmlElement(windowData, "Switchable", wProperties.switchableToOtherModes);

        ReadFromXmlElement(windowData, "ResolutionWidth", wProperties.width);
        ReadFromXmlElement(windowData, "ResolutionHeight", wProperties.height);
        
        int cursorMode(-1);
        ReadFromXmlElement(windowData, "CursorMode", cursorMode);
        switch (cursorMode)
        {
        case 0:
            wProperties.cursorMode = CursorMode::DISABLED;
            break;
        case 1:
            wProperties.cursorMode = CursorMode::VISIBLE;
            break;
        case 2:
            wProperties.cursorMode = CursorMode::HIDDEN;
            break;
        default:
            Debug::LogError("Could not find a correct CursorMode property in the window properties file");
            break;
        }
        
        return wProperties;
    }

}
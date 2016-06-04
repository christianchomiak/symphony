#include "Window.h"

#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"


void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    Symphony::Window* w = static_cast<Symphony::Window*>(glfwGetWindowUserPointer(window));
    w->HandleResize();
}

namespace Symphony
{
    Window::Window(const char* title, int width, int height, bool resizeable, bool decorated, bool maximised, bool switchableToFullscreen)
        : properties(title, width, height, false, resizeable, decorated, maximised, switchableToFullscreen, CursorMode::NORMAL)
    {
        window = nullptr;
    }
    
    Window::Window(const char* title, int width, int height, bool switchableToWindowed)
        : properties(title, width, height, true, false, false, false, false, CursorMode::NORMAL)
    {
        window = nullptr;
    }

    Window::Window(WindowProperties& initialProperties)
        : properties(initialProperties)
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

        if (properties.fullscreen)
        {
            window = glfwCreateWindow(properties.width, properties.height, properties.title, glfwGetPrimaryMonitor(), NULL);
        }
        else
        {
            glfwWindowHint(GLFW_RESIZABLE, properties.resizeable ? GL_TRUE : GL_FALSE);
            glfwWindowHint(GLFW_DECORATED, properties.decorated ? GL_TRUE : GL_FALSE);
            glfwWindowHint(GLFW_MAXIMIZED, properties.maximised ? GL_TRUE : GL_FALSE);
            
            window = glfwCreateWindow(properties.width, properties.height, properties.title, NULL, NULL);
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

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            Debug::LogError("Could not initialise GLEW!");
            return false;
        }
        
        HandleResize();
        //glViewport(0, 0, width, height);
        OutputRenderingInfo();

        ChangeCursorMode(properties.cursorMode);

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
        //TO-DO: check if this might cause a memory leak
        properties.title = newName;
        glfwSetWindowTitle(window, properties.title);
    }

    void Window::HandleResize()
    {
        //glfwGetWindowSize(window, &width, &height);

        glfwGetFramebufferSize(window, &properties.width, &properties.height);
        glViewport(0, 0, properties.width, properties.height);
    }

    void Window::OutputRenderingInfo() const
    {
        std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        printf("Running against GLFW %i.%i.%i\n", major, minor, revision);
    }

    void Window::ChangeCursorMode(CursorMode newMode)
    {
        properties.cursorMode = newMode;

        switch (properties.cursorMode)
        {
        case CursorMode::DISABLED:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        case CursorMode::NORMAL:
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
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, properties.width, properties.height, GLFW_DONT_CARE); 
            // mode->width, mode->height, GLFW_DONT_CARE);// mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(window, NULL, 0, 0, properties.width, properties.height, GLFW_DONT_CARE);
        }
        
        HandleResize();
    }

    void Window::glfwErrorCallback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

}
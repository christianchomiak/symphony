#include "Window.h"

#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"


void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    Symphony::Window* w = static_cast<Symphony::Window*>(glfwGetWindowUserPointer(window));
    w->HandleResize();
}

Symphony::Window::Window(const char* name, int width, int height)
{
    this->name = name;
    this->width = width;
    this->height = height;
    cursorMode = CursorMode::NORMAL;
    window = nullptr;
}

Symphony::Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    
    //TO-DO: is `window` being freed by glfwTerminate?
    //delete window;
}

bool Symphony::Window::Initialise()
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
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    window = glfwCreateWindow(width, height, name, NULL, NULL);
    
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

    glViewport(0, 0, width, height);
    OutputRenderingInfo();

    ChangeCursorMode(cursorMode);

    return true;
}

void Symphony::Window::Clear() const
{
    //glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Symphony::Window::SwapBuffers() const
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

void Symphony::Window::Update()
{
    /* Poll for and process events */
    glfwPollEvents();
}

bool Symphony::Window::Closed() const
{
    return glfwWindowShouldClose(window) == 1;
}

void Symphony::Window::ChangeName(const char* newName)
{
    //TO-DO: check if this might cause a memory leak
    name = newName;
    glfwSetWindowTitle(window, name);
}

void Symphony::Window::HandleResize()
{    
    //glfwGetWindowSize(window, &width, &height);
    
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void Symphony::Window::OutputRenderingInfo() const
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

void Symphony::Window::ChangeCursorMode(CursorMode newMode)
{
    cursorMode = newMode;
    
    switch (cursorMode)
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

void Symphony::Window::glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
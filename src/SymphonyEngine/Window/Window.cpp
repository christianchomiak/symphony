#include "Window.h"

#include "../Debugging/Debugging.h"

//TO-DO: Figure out a better way to avoid having to use a boolean
//       to check if the window was resized and instead handle the resizeing right away
bool Symphony::Window::windowResized = false;

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    Symphony::Window::windowResized = true;
}

Symphony::Window::Window(const char * name, int width, int height)
{
    this->name = name;
    this->width = width;
    this->height = height;
    window = nullptr;
}

Symphony::Window::~Window()
{
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

    window = glfwCreateWindow(width, height, name, NULL, NULL);
    
    if (!window)
    {
        Debug::LogError("Failed to initialise window");
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        Debug::LogError("Could not initialise GLEW!");
        return false;
    }

    std::cout << "Using OpenGL " << glGetString(GL_VERSION) << std::endl;
    //Debug::Log();

    return true;
}

void Symphony::Window::Clear() const
{
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Symphony::Window::Update()
{
    /* Poll for and process events */
    glfwPollEvents();

    //Resize window
    if (Window::windowResized) HandleResize();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
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
    Symphony::Window::windowResized = false;
    
    //glfwGetWindowSize(window, &width, &height);
    
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

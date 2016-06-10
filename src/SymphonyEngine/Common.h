#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLFW/glfw3.lib")
#pragma comment(lib, "GLEW/glew32s.lib")

#ifdef _DEBUG
#pragma comment(lib, "SOIL2/soil2-debug.lib")
#else
#pragma comment(lib, "SOIL2/soil2.lib")
#endif
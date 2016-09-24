#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLFW/glfw3.lib")
#pragma comment(lib, "GLEW/glew32s.lib")

//TO-DO: Maybe _DEBUG should be aliased to account for multiplatforming
#ifdef _DEBUG
#   pragma comment(lib, "SOIL2/soil2-debug.lib")
#   pragma comment(lib, "FreeType/freetyped.lib")
#   pragma comment(lib, "TinyXML2/tinyxml2d.lib")
#else
#   pragma comment(lib, "SOIL2/soil2.lib")
#   pragma comment(lib, "FreeType/freetype.lib")
#   pragma comment(lib, "TinyXML2/tinyxml2.lib")
#endif

/*#ifdef _WIN64
...
#else
...
#endif*/
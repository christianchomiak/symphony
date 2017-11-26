#pragma once

#include <Macros/ClassMacros.h>

namespace Symphony
{
    class ImGuiManager
    {
        friend class SymphonyEngine;
    public:
        ImGuiManager()
        {
        }

        ~ImGuiManager()
        {
        }

        NO_ASSIGNMENT_OPERATOR(ImGuiManager)
        NO_COPY_CONSTRUCTOR(ImGuiManager)

        void PrepareForNewFrame(float deltaTime, bool windowIsFocused, int windowWidth, int windowHeight, int windowFrameBufferWidth, int windowFrameBufferHeight);
        void Render(int windowWidth, int windowHeight, int windowFrameBufferWidth, int windowFrameBufferHeight);

        bool IsImGuiDrawingCursor() const;
        static bool WantsToCaptureKeyboard();

    protected:
        unsigned int g_FontTexture = 0;

        int g_ShaderHandle  = 0,
            g_VertHandle    = 0,
            g_FragHandle    = 0;

        int g_AttribLocationTex      = 0,
            g_AttribLocationProjMtx  = 0;

        int g_AttribLocationPosition = 0,
            g_AttribLocationUV       = 0,
            g_AttribLocationColor    = 0;

        unsigned int g_VboHandle = 0,
                     g_VaoHandle = 0,
                     g_ElementsHandle = 0;

        bool ImGui_ImplGlfwGL3_CreateFontsTexture();
        void RenderDrawLists(void* draw_data);
        
        // Use if you want to reset your rendering device without losing ImGui state.
        void InvalidateDeviceObjects();
        bool CreateDeviceObjects();
        
        void Shutdown();

    public /*static*/:
        
        static bool Init(void* window);  //GLFWwindow* window, bool install_callbacks);

        // GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
        // Provided here if you want to chain callbacks.
        // You can also handle inputs yourself and use those as a reference.
        static void ImGui_ImplGlfwGL3_KeyCallback(int key, int scancode, int action, int mods);
        static void ImGui_ImplGlfwGL3_CharCallback(unsigned int c);
    };
}
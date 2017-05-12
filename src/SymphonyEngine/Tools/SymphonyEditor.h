#pragma once

#include "ImGuiMemoryEditor.h"

namespace Symphony
{
    class SymphonyEditor
    {
    public:
        SymphonyEditor();
        ~SymphonyEditor();

        void Update();

    protected:
        MemoryEditor memoryEditor;
        bool inEditorMode;

        void DrawMainMenuBar();
    };
}
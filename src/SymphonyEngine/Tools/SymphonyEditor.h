#pragma once

#include "ImGuiMemoryEditor.h"

namespace Symphony
{
    class Scene;
    class GameObject;

    class SymphonyEditor
    {
    public:
        SymphonyEditor();
        ~SymphonyEditor();

        void Update(Scene* currentScene);

    protected:
        bool inEditorMode;
        MemoryEditor memoryEditor;
        
        void DrawMainMenuBar();
        void DrawSceneTree(Scene* currentScene);
        void DrawSceneTreeNode(const GameObject* root);
    };
}
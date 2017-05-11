#include "SymphonyEditor.h"

#include <imgui\imgui.h>

namespace Symphony
{
    SymphonyEditor::SymphonyEditor()
    {

    }

    SymphonyEditor::~SymphonyEditor()
    {
    }

    void SymphonyEditor::Update()
    {
        {
            //ImGui::ShowTestWindow();

            static bool menuEnabled = false;

            static bool itemSelected = false;
            static bool itemEnabled = false;

            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("Symphony Engine", true))
                {
                    ImGui::MenuItem("Test", NULL, itemSelected, itemEnabled);
                    ImGui::EndMenu();
                }
                
                ImGui::SameLine();
                ImGui::Separator();
                ImGui::SameLine();
                
                ImGui::Text("| %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                ImGui::EndMainMenuBar();
            }
        }

        //memoryEditor.Draw("Memory Editor", mem_block, mem_block_size, (size_t)mem_block);
    }
}

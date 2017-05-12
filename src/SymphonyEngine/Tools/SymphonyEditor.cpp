#include "SymphonyEditor.h"

#include <imgui/imgui.h>
#include "../Input/InputManager.h"
#include "../Time/Time.h"

namespace Symphony
{
    SymphonyEditor::SymphonyEditor()
    {

    }

    SymphonyEditor::~SymphonyEditor()
    {
    }

    void SymphonyEditor::DrawMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            ImGui::Text("Symphony Engine");

                ImGui::SameLine();

            ImGui::Text("| %s Mode |", InputManager::InputIsBlocked() ? "Editor" : "Game");

                ImGui::SameLine();

            ImGui::Checkbox("Paused", &Time::paused);

                ImGui::SameLine();

            ImGui::Text("| Frame %llu, %.3f ms (%.1f FPS) |", Time::frame, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                        
            ImGui::EndMainMenuBar();
        }
    }

    void SymphonyEditor::Update()
    {
        DrawMainMenuBar();

        //ImGui::ShowTestWindow();

        /*static char input[128] = "Enter something...";

        ImGuiIO& io = ImGui::GetIO();

        ImGui::InputText("Input", input, 128);

        {
            static bool menuEnabled = false;

            static bool itemSelected = false;
            static bool itemEnabled = false;

            
        }*/

        //memoryEditor.Draw("Memory Editor", mem_block, mem_block_size, (size_t)mem_block);
    }
}

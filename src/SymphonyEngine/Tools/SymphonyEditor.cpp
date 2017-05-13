#include "SymphonyEditor.h"

#include <imgui/imgui.h>
#include "../Scene/Scene.h"
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
            if (ImGui::BeginMenu("Symphony Engine"))
            {
                if (ImGui::MenuItem("Exit", "ESC")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                ImGui::MenuItem("Symphony v0.1", NULL, false, false);
                ImGui::EndMenu();
            }
            /*if (ImGui::BeginMenu("Edit"))
            {
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }*/

            ImGui::SameLine();

            ImGui::Text("| %s Mode |", InputManager::InputIsBlocked() ? "Editor" : "Game");

                ImGui::SameLine();

            ImGui::Checkbox("Paused", &Time::paused);

                ImGui::SameLine();

            ImGui::Text("| Frame %llu, %.3f ms (%.1f FPS) |", Time::frame, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                        
            ImGui::EndMainMenuBar();
        }
    }

    void SymphonyEditor::DrawSceneTree(Scene* currentScene)
    {
        static bool p_open = true;
        
        ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiSetCond_Once);

        if (!ImGui::Begin("Scene Tree", &p_open))
        {
            ImGui::End();
            return;
        }

        //ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

        static bool align_label_with_current_x_position = false;
        ImGui::Checkbox("Align label with current X position)", &align_label_with_current_x_position);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        ImGui::Columns(2);
        ImGui::Separator();

        //ShowHelpMarker("This is a more standard looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.");

        ImGui::Text("Gameplay");

        if (align_label_with_current_x_position)
            ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());

        DrawSceneTreeNode(currentScene->GetSceneRoot());

        ImGui::Text("UI");
        DrawSceneTreeNode(currentScene->GetSceneUIRoot());

        ImGui::NextColumn();
        ImGui::AlignFirstTextHeightToWidgets();
        ImGui::Text("my sailor is rich");

        ImGui::NextColumn();

        if (align_label_with_current_x_position)
            ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

        /*if (ImGui::TreeNode("Root"))
        {

            static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
            
            ImGui::TreePop();
        }*/

        /*struct funcs
        {
            static void ShowDummyObject(const char* prefix, int uid)
            {
                ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
                ImGui::AlignFirstTextHeightToWidgets();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
                bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
                
                ImGui::NextColumn();

                ImGui::AlignFirstTextHeightToWidgets();
                ImGui::Text("my sailor is rich");
                ImGui::NextColumn();
                if (node_open)
                {
                    static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
                    for (int i = 0; i < 8; i++)
                    {
                        ImGui::PushID(i); // Use field index as identifier.
                        if (i < 2)
                        {
                            ShowDummyObject("Child", 424242);
                        }
                        else
                        {
                            ImGui::AlignFirstTextHeightToWidgets();
                            // Here we use a Selectable (instead of Text) to highlight on hover
                            //ImGui::Text("Field_%d", i);
                            char label[32];
                            sprintf(label, "Field_%d", i);
                            ImGui::Bullet();
                            ImGui::Selectable(label);
                            ImGui::NextColumn();
                            ImGui::PushItemWidth(-1);
                            if (i >= 5)
                                ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
                            else
                                ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
                            ImGui::PopItemWidth();
                            ImGui::NextColumn();
                        }
                        ImGui::PopID();
                    }
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        };*/

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::End();
    }

    void SymphonyEditor::DrawSceneTreeNode(const GameObject* root)
    {
        if (!root)
        {
            return;
        }


        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 2); // Increase spacing to differentiate leaves from expanded contents.
        
        static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.

        // Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick; // | ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected : 0);
        
        const auto& children = root->GetChildren();
        if (children.size() == 0)
        {
            // Leaf: The only reason we have a TreeNode at all is to allow selection of the leaf. Otherwise we can use BulletText() or TreeAdvanceToLabelPos()+Text().
            ImGui::TreeNodeEx((void*)root, node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, root->name.c_str());
            /*if (ImGui::IsItemClicked())
            {
                node_clicked = i;
            }*/
        }
        else
        {
            // Node
            bool node_open = ImGui::TreeNodeEx((void*)root, node_flags, root->name.c_str());
            /*if (ImGui::IsItemClicked())
            {
                node_clicked = i;
            }*/
            if (node_open)
            {
                for (const GameObject* o : root->GetChildren())
                {
                    DrawSceneTreeNode(o);
                }
                ImGui::TreePop();
            }
        }

        ImGui::PopStyleVar();
    }

    void SymphonyEditor::Update(Scene* currentScene)
    {
        bool showDemo = false;

        if (!showDemo)
        {
            DrawMainMenuBar();
            DrawSceneTree(currentScene);
        }
        else
        {
            ImGui::ShowTestWindow();
        }


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

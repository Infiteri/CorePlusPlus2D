#include "SceneHierarchyPanel.h"
#include <algorithm>
#include "EditorUtils.h"
#include <imgui.h>
#include "Core.h"

namespace Core
{
    static const ImGuiTreeNodeFlags ActorNodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap;

    void SceneHierarchyPanel::RenderGUIActor(Actor *a)
    {
        ImGuiTreeNodeFlags ActiveFlags = ActorNodeFlags;

        if (selectionContext && selectionContext->GetUUID()->SameAs(a->GetUUID()))
            ActiveFlags |= ImGuiTreeNodeFlags_Selected;

        bool Opened = ImGui::TreeNodeEx((void *)a->GetUUID()->Get(), ActiveFlags, a->GetName().c_str());
        if (ImGui::IsItemClicked())
            selectionContext = a;

        if (Opened)
        {
            ImGui::TreePop();
        }
    }

    // -- DRAW UI METHODS --
    void DrawMeshUI(MeshComponent *m, Actor *a);
    // ---------------------

    void SceneHierarchyPanel::RenderGUIActorProperties(Actor *a)
    {
        //? Name
        {
            static char Buffer[256];
            CeMemory::Zero(Buffer, 256);
            CeMemory::Copy(Buffer, a->GetName().c_str(), a->GetName().size());

            if (ImGui::InputText("Name", Buffer, 256))
                a->SetName(Buffer);
        }

        //? Transform
        {
            if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                Transform *t = a->GetTransform();
                EditorUtils::RenderGUITransform(t);
                ImGui::TreePop();
            }
        }

        //? UI Components
        {
            EditorUtils::DrawComponentUI<MeshComponent>("Mesh Component", a, [&](MeshComponent *m)
                                                        { DrawMeshUI(m, a); });
        }
    }

    void SceneHierarchyPanel::RenderGUI()
    {
        Scene *active = World::GetActiveScene();
        if (!active)
            return;

        ImGui::Begin("Scene Hierarchy");

        for (auto a : active->GetActors())
            RenderGUIActor(a);

        ImGui::Begin("Properties");
        if (selectionContext)
            RenderGUIActorProperties(selectionContext);
        ImGui::End();

        ImGui::End();
    }

    // -- UI

    void DrawMeshUI(MeshComponent *m, Actor *a)
    {
        if (ImGui::TreeNodeEx("Material"))
        {
            if (m->mesh->IsMaterialUnique())
            {
                EditorUtils::RenderGUIColor("Color", m->mesh->GetMaterial()->GetColor());

                // - Texture
                {
                    if (ImGui::TreeNode("Texture"))
                    {
                        auto matTexture = m->mesh->GetMaterial()->GetColorTexture();
                        auto texture = matTexture->GetType() == Texture::WhiteDefault ? EditorUtils::GetDefaultEmptyTexture() : matTexture;

                        {
                            float imageWidth = texture->GetWidth();
                            float imageHeight = texture->GetHeight();
#define CalcTextAsp(n) 64 / (imageWidth / imageHeight)

                            ImGui::Image((void *)(CeU64)(CeU32)texture->GetID(), {CalcTextAsp(imageWidth), CalcTextAsp(imageHeight)});
                        }

                        auto img = texture->GetImage();
                        if (ImGui::IsItemHovered() && img)
                        {
                            ImGui::SetNextWindowSize({700, 128});
                            ImGui::SetNextWindowPos({ImGui::GetWindowPos().x + 250, ImGui::GetWindowPos().y + 100});
                            ImGui::SetWindowFontScale(2);
                            ImGui::Begin("Window Props");
                            ImGui::Text("Source: %s.", img->GetName().c_str());
                            ImGui::Text("W/H/C: %i / %i / %i.", img->GetWidth(), img->GetHeight(), img->GetChannels());
                            ImGui::End();
                            ImGui::SetWindowFontScale(1);
                        }

                        if (ImGui::Button("Load Image"))
                        {
                            std::string location = Platform::OpenFileDialog("Images. \0*.png; *.jpg; *.jpeg \0 \0*.png; *.jpg; *.jpeg\0");
                            if (!location.empty())
                                m->mesh->GetMaterial()->GetColorTexture()->Load(location);
                        }

                        ImGui::TreePop();
                    }
                }
            }
            else // ! MATERIAL IS NOT UNIQUE
                ImGui::Text("Material is a loaded material. (%s)", m->mesh->GetMaterial()->GetName().c_str());

            if (ImGui::Button("Load From File"))
            {
                std::string location = Platform::OpenFileDialog("Images. \0*.ce_mat\0");
                std::replace(location.begin(), location.end(), '\\', '/');
                CE_CORE_DEBUG("Location: %s", location.c_str()); //? Da fuq? Why is it using \\ instead of /
                if (!location.empty())
                    m->mesh->SetMaterial(location.c_str());
            }
            ImGui::TreePop();
        }
    }
}
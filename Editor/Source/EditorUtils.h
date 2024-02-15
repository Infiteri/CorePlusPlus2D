#pragma once

#include "Core.h"
#include "Renderer/Color.h"
#include "Math/Vectors.h"
#include "Math/Transform.h"
#include "Renderer/Texture/Texture.h"
#include <imgui.h>

namespace Core
{
    namespace EditorUtils
    {
        Texture *GetDefaultEmptyTexture();

        void RenderGUIColor(const char *name, Color *c);
        void RenderGUIVector3(const char *name, Vector3 *v);
        void RenderGUITransform(Transform *t);

        template <typename T, typename UIFun>
        void DrawComponentUI(const std::string &name, Actor *a, UIFun fun)
        {
            const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen;

            if (a->HasComponent<T>())
            {
                auto comp = a->GetComponent<T>();

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
                bool open = ImGui::TreeNodeEx((void *)typeid(T).hash_code(), flags, name.c_str());
                bool removeComp = false;

                ImGui::PopStyleVar();

                if (open)
                {
                    fun(comp);
                    if (ImGui::Button("Remove"))
                    {
                        removeComp = true;
                    };
                    ImGui::TreePop();
                }

                if (removeComp)
                    a->RemoveComponent<T>();
            }
        }

    };
}
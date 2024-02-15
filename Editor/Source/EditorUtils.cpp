#include "EditorUtils.h"
#include <imgui_internal.h>

namespace Core
{
    namespace EditorUtils
    {
        static void TRANSFORM_GUI_VectorEdit(const char *label, Vector3 *vec, float valueDefault);
        void TRANSFORM_GUI_VectorEdit(const char *label, Vector3 *vec, float valueDefault)
        {
            ImGui::PushID(label);

            ImGui::Columns(2);

            ImGui::SetColumnWidth(0, 50.0f);
            ImGui::Text(label);
            ImGui::NextColumn();
            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

            float lineH = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImVec2 buttonSize = {lineH + 3.0f, lineH};
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
            if (ImGui::Button("X", buttonSize))
            {
                vec->x = valueDefault;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##x", &vec->x, 0.01f);
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
            if (ImGui::Button("Y", buttonSize))
            {
                vec->y = valueDefault;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##y", &vec->y, 0.01f);
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
            if (ImGui::Button("Z", buttonSize))
            {
                vec->z = valueDefault;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##z", &vec->z, 0.01f);
            ImGui::PopItemWidth();
            ImGui::PopStyleVar();

            ImGui::Columns(1);

            ImGui::PopID();
        }

        void RenderGUITransform(Transform *t)
        {
            TRANSFORM_GUI_VectorEdit("Position", &t->Position, 0);
            TRANSFORM_GUI_VectorEdit("Rotation", &t->Rotation, 0);
            TRANSFORM_GUI_VectorEdit("Scale", &t->Scale, 1);
        }

        static Texture *defTexture = nullptr;
        Texture *GetDefaultEmptyTexture()
        {
            if (!defTexture)
            {
                const int size = 10;
                CeU8 *data;

                data = new CeU8[size * size * 4];
                for (CeU32 y = 0; y < size; ++y)
                {
                    for (CeU32 x = 0; x < size; ++x)
                    {
                        CeU8 color = ((x / 5) + (y / 5)) % 2 == 0 ? 255 : 200; // Alternate between white (255) and light gray (200)
                        CeU32 pixelOffset = (y * size + x) * 4;
                        data[pixelOffset] = color;     // Red
                        data[pixelOffset + 1] = color; // Green
                        data[pixelOffset + 2] = color; // Blue
                        data[pixelOffset + 3] = 255;   // Alpha (fully opaque)
                    }
                }

                defTexture = new Texture();
                defTexture->Load(data, size, size, 4);
            }

            return defTexture;
        }

        void RenderGUIColor(const char *name, Color *c)
        {
            float edit[4] = {c->r / 255, c->g / 255, c->b / 255, c->a / 255};

            if (ImGui::ColorEdit4(name, edit))
                c->Set(edit[0] * 255, edit[1] * 255, edit[2] * 255, edit[3] * 255);
        }

        void RenderGUIVector3(const char *name, Vector3 *v)
        {
            float data[3] = {v->x, v->y, v->z};
            ImGui::DragFloat3(name, data, 0.05f);
            {
                v->x = data[0];
                v->y = data[1];
                v->z = data[2];
            }
        }
    }
}
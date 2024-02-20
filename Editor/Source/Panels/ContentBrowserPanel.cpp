#include "ContentBrowserPanel.h"
#include "Utils/StringUtils.h"
#include "EditorLayer.h"
#include <imgui.h>
#include "Core.h"

namespace Core
{
    static float padding = 16.0f;
    static float thumbnailSize = 64.0f;
    static float cellSize = thumbnailSize + padding;
    static std::string activePath;
    static bool pressedFolder = false;

    void ContentBrowserPanel::OnImGuiRender()
    {
        if (activePath.empty())
            activePath = BaseDirectoryPath;

        ImGui::Begin("Content Browser");

        auto textures = &EditorLayer::GetInstance()->state.textureCollection;
        auto entries = Platform::GetDirectoryEntries(activePath);

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1)
            columnCount = 1;
        ImVec2 size{thumbnailSize, thumbnailSize}; // Might change based on preferences
        ImGui::Columns(columnCount, 0, false);

        if (activePath.compare(BaseDirectoryPath) != 0 && ImGui::Button("<-"))
            activePath = BaseDirectoryPath;

        int it = 0;
        for (auto &entry : entries)
        {
            it++;
            ImGui::PushID(it);

            auto texture = entry.IsFolder ? textures->FolderTexture : textures->IconTexture;
            if (ImGui::ImageButton((void *)(CeU64)(CeU32)(texture->GetID()), size))
            {
                if (entry.IsFolder)
                {
                    pressedFolder = true;
                    activePath += "/" + entry.Filename;
                }
                else
                    pressedFolder = false;
            }

            if (!entry.IsFolder)
                ImGui::TextWrapped(StringUtils::GetFileName(entry.Filename).c_str());
            else
                ImGui::TextWrapped(entry.Filename.c_str());

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::End();
    }
}

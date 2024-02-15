
#include "EditorLayer.h"
#include <imgui.h>

namespace Core
{
    struct
    {
        bool dockspaceOpen = true;
        bool opt_fullscreen = true;
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImVec2 lastFrameViewportSize;
    } state;

    void EditorSceneViewport::RenderGUIDockspace()
    {
        if (state.opt_fullscreen)
        {
            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            state.window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            state.window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (state.dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            state.window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &state.dockspaceOpen, state.window_flags);
        ImGui::PopStyleVar();

        if (state.opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 250.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), state.dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::PopStyleVar();
    }

    void EditorSceneViewport::RenderGUI()
    {
        Scene *active = World::GetActiveScene();
        if (!active)
            return;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        ImGui::PopStyleVar();

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (viewportSize.x != state.lastFrameViewportSize.x || viewportSize.y != state.lastFrameViewportSize.y)
        {
            state.lastFrameViewportSize = viewportSize;
            EditorLayer::STATIC_EDITOR_UTIL_ResizeViewport({viewportSize.x, viewportSize.y});
        }


        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0, 0});
        ImGui::Image((void *)(CeU64)(CeU32)(Renderer::GetFrameBuffer()->GetRenderPass(0)->id), viewportSize, ImVec2{0, 1}, ImVec2{1, 0});
        ImGui::PopStyleVar();


        if (EditorSceneConfig)
            EditorSceneConfig->MidSceneViewportRenderCall(active);

        ImGui::End();
    }

    void EditorSceneViewport::RenderGUIDockspaceEnd()
    {
        ImGui::End();
    }
}
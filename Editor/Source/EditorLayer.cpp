#include "EditorLayer.h"
#include <imgui.h>

namespace Core
{
    EditorLayer::EditorLayer()
    {
        {
            ICoreEditorSceneViewportConfiguration *configViewport = new CoreEditorViewportConfiguration();
            state.editorSceneViewport.EditorSceneConfig = configViewport;
        }
    }

    EditorLayer::~EditorLayer()
    {
        delete state.editorSceneViewport.EditorSceneConfig;
    }

    void EditorLayer::OnAttach()
    {
        // Scene *scene = World::CreateScene("New_Scene");
        // auto a = scene->SpawnActor<Actor>();
        // a->SetName("Mesh Actor");
        // auto m = a->AddComponent<MeshComponent>();

        // m->mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");
        // m->mesh->SetGeometry(new SquareGeometry(100, 100));
        state.saveScenePath = "EngineResources/Scenes/Main.ce_scene"; // TODO: Change
        OpenScene(state.saveScenePath);
        World::GetActiveScene()->GetActors()[0]->GetComponent<MeshComponent>()->mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");
        World::GetActiveScene()->GetActors()[0]->GetComponent<MeshComponent>()->mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");

        World::GetActiveScene()->GetActors()[0]->GetComponent<MeshComponent>()->mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");
        World::GetActiveScene()->GetActors()[0]->GetComponent<MeshComponent>()->mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");
        World::StartActiveScene();
    }

    void EditorLayer::OnImGuiRender()
    {
        state.editorSceneViewport.RenderGUIDockspace();

        // -- UI --
        UI_RenderTopToolBar();
        // --------

        ImGui::Begin("Color Editor Edit");
        UTIL_ColorThing("Window Bg", ImGuiCol_WindowBg);
        UTIL_ColorThing("Header", ImGuiCol_Header);
        UTIL_ColorThing("HeaderHovered", ImGuiCol_HeaderHovered);
        UTIL_ColorThing("HeaderActive", ImGuiCol_HeaderActive);
        UTIL_ColorThing("Button", ImGuiCol_Button);
        UTIL_ColorThing("ButtonHovered", ImGuiCol_ButtonHovered);
        UTIL_ColorThing("ButtonActive", ImGuiCol_ButtonActive);
        UTIL_ColorThing("FrameBg", ImGuiCol_FrameBg);
        UTIL_ColorThing("FrameBgHovered", ImGuiCol_FrameBgHovered);
        ImGui::End();

        state.hierarchyPanel.RenderGUI();

        state.editorSceneViewport.RenderGUI();
        state.editorSceneViewport.RenderGUIDockspaceEnd();
    }

    void EditorLayer::UI_RenderTopToolBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::MenuItem("File"))
                ImGui::OpenPopup("FILE_POPUP_CORE");

            if (ImGui::BeginPopup("FILE_POPUP_CORE"))
            {
                if (ImGui::MenuItem("Save"))
                    SaveScene();

                if (ImGui::MenuItem("Save As"))
                    SaveSceneAs();

                if (ImGui::MenuItem("Open"))
                    OpenScene();

                ImGui::EndPopup();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EditorLayer::OpenScene()
    {
        std::string name = Platform::OpenFileDialog("Core Scene (*.ce_scene)\0*.ce_scene\0");
        if (!name.empty())
            OpenScene(name);
    }

    void EditorLayer::OpenScene(const std::string &name)
    {
        state.saveScenePath = name;
        SceneSerializer serialize{World::GetActiveScene()};
        serialize.DeserializeAndCreateNew(name);

        World::InitializeActiveScene();
    }

    void EditorLayer::SaveSceneAs()
    {
        std::string location = Platform::SaveFileDialog("Scene (\0*.ce_scene\0) \0*.ce_scene\0");
        if (!location.empty())
        {
            state.saveScenePath = location;
            SceneSerializer serializer(World::GetActiveScene());
            serializer.Serialize(location);
        }
    }

    void EditorLayer::SaveScene()
    {
        if (state.saveScenePath.empty())
        {
            SaveSceneAs();
        }

        SceneSerializer serializer(World::GetActiveScene());
        serializer.Serialize(state.saveScenePath);
    }

    //? CORE STATIC ---

    void EditorLayer::STATIC_EDITOR_UTIL_ResizeViewport(const Vector2 &viewport)
    {
        Renderer::ResizeViewport({(int)viewport.x, (int)viewport.y});
    }

    void EditorLayer::UTIL_ColorThing(const char *label, int target)
    {
        auto &colors = ImGui::GetStyle().Colors;

        float data[4] = {colors[target].x, colors[target].y, colors[target].z, colors[target].w};
        if (ImGui::ColorEdit4(label, data))
        {
            colors[target].x = data[0];
            colors[target].y = data[1];
            colors[target].z = data[2];
            colors[target].w = data[3];
        }
    }

    //? END CORE STATIC

    void CoreEditorViewportConfiguration::MidSceneViewportRenderCall(Scene *scene)
    {
    }
}
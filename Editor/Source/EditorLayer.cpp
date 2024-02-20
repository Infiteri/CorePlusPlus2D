#include "EditorLayer.h"

namespace Core
{
    static EditorLayer *inst;

    EditorLayer::EditorLayer()
    {
    }

    EditorLayer::~EditorLayer()
    {
        delete state.textureCollection.IconPlayTexture;
        delete state.textureCollection.IconStopTexture;
    }

    void EditorLayer::OnAttach()
    {
        inst = this;
        state.textureCollection.Init();
        state.Editorcamera = new OrthographicCamera(Engine::GetWindow()->GetWidth(), Engine::GetWindow()->GetHeight());
        CameraSystem::AddOrthographicCamera(state.Editorcamera, "EditorCamera");
        state.Editorcamera->SetOriginPoint(OrthographicCamera::Middle);
        state.Editorcamera->SetZoom(5);
        state.EditorScene = nullptr;
        StopSceneRuntime();

        // Scene *scene = World::CreateScene("New_Scene");
        // auto a = scene->SpawnActor<Actor>();
        // a->SetName("Mesh Actor");
        // auto m = a->AddComponent<MeshComponent>();

        // m->mesh->SetMaterial("EngineResources/Materials/Test.ce_mat");
        // m->mesh->SetGeometry(new SquareGeometry(100, 100));
        state.saveScenePath = "EngineResources/Scenes/Main.ce_scene"; // TODO: Change
        OpenScene(state.saveScenePath);
    }

    void EditorLayer::OnUpdate()
    {
        if (currentSceneState == SceneStatePlay)
            UpdateRuntime();
        else
            UpdateEditor();
    }

    void EditorLayer::OnImGuiRender()
    {
        state.editorSceneViewport.RenderGUIDockspace();

        // -- UI --
        UI_RenderTopToolBar();
        UI_RenderPlaySceneBar();
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
        ImGui::Text("Delta: %f", (float)Engine::GetDeltaTime());
        ImGui::Text("FPS: %i", (int)(1.0 / Engine::GetDeltaTime()));
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

    void EditorLayer::UI_RenderPlaySceneBar()
    {
        ImGui::Begin("##topbar");

        Texture *tex = currentSceneState == SceneStatePlay ? state.textureCollection.IconStopTexture : state.textureCollection.IconPlayTexture;
        if (ImGui::ImageButton((ImTextureID)(CeU64)(CeU32)tex->GetID(), {12, 12}))
        {
            if (currentSceneState == SceneStatePlay)
                StopSceneRuntime();
            else
                StartSceneRuntime();
        }

        ImGui::End();
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

    void EditorLayer::StartSceneRuntime()
    {
        currentSceneState = SceneStatePlay;

        state.EditorScene = Scene::Copy(World::GetActiveScene());
        World::StartActiveScene();

        if (!Renderer::GetViewport())
        {
            return;
        }
        CameraSystem::GetActiveAsOrtho()->CalculateProjection(Renderer::GetViewport()->width, Renderer::GetViewport()->height);
    }

    void EditorLayer::StopSceneRuntime()
    {
        currentSceneState = SceneStateStop;

        World::StopActiveScene();
        if (state.EditorScene != nullptr)
        {
            World::CopyToActive(state.EditorScene);
            delete state.EditorScene;
            World::InitializeActiveScene();
        }

        CameraSystem::Activate("EditorCamera");
    }

    void EditorLayer::UpdateRuntime()
    {
        World::UpdateActiveScene();
    }

    void EditorLayer::UpdateEditor()
    {
        // ? camera movement
        {
            auto cam = state.Editorcamera;
            if (!cam)
                return;

            auto mousePos = Input::GetMousePosition();
            auto mouseDelta = Input::GetMouseDelta();
            auto windowPos = Vector2(Engine::GetWindow()->GetX(), Engine::GetWindow()->GetY());

            if (Input::GetButton(Input::ButtonRight))
            {
                if (mousePos.x > state.LeftTopViewport.x + windowPos.x &&
                    mousePos.x < state.BottomRightViewport.x + state.LeftTopViewport.x + windowPos.x &&
                    mousePos.y > state.LeftTopViewport.y + windowPos.y &&
                    mousePos.y < state.BottomRightViewport.y + state.LeftTopViewport.y + windowPos.y)
                {
                    cam->GetPosition()->x += mouseDelta.x;
                    cam->GetPosition()->y += mouseDelta.y;
                }
            }

            float ScrollDelta = Input::GetMouseWheelDelta();
            if (Input::GetKey(Input::LeftControl) && ScrollDelta != 0)
            {
                state.Editorcamera->AddZoom(ScrollDelta * 0.05);
            }
        }
    }

    //? CORE STATIC ---

    void EditorLayer::STATIC_EDITOR_UTIL_ResizeViewport(const Vector2 &viewport)
    {
        Renderer::ResizeViewport({(int)viewport.x, (int)viewport.y});
    }

    void EditorLayer::STATIC_EDITOR_UTIL_MidSceneRender(Scene *active)
    {

        // inst->state.LeftTopViewport = ImGui::GetWindowPos();
        // inst->state.BottomRightViewport = ImGui::GetWindowSize();
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

    void TextureCollection::Init()
    {
        IconPlayTexture = new Texture("EngineResources/Images/Icons/PlayButton.png");
        IconStopTexture = new Texture("EngineResources/Images/Icons/StopButton.png");
    }

    EditorLayer *EditorLayer::GetInstance()
    {
        return inst;
    }
}
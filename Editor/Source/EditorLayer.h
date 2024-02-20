#pragma once

#include "Core.h"
#include "EditorSceneViewport.h"
#include "Panels/SceneHierarchyPanel.h"
#include <imgui.h>

namespace Core
{
    struct TextureCollection
    {
        Texture *IconPlayTexture;
        Texture *IconStopTexture;

        void Init();
    };

    struct EditorState
    {
        EditorSceneViewport editorSceneViewport;
        SceneHierarchyPanel hierarchyPanel;
        TextureCollection textureCollection;

        std::string saveScenePath;

        Scene *EditorScene;
        OrthographicCamera *Editorcamera;
        Vector2 Viewport;

        ImVec2 LeftTopViewport;
        ImVec2 BottomRightViewport;
    };

    class EditorLayer : public Layer
    {
    public:
        EditorState state;

        EditorLayer();
        ~EditorLayer();

        void OnAttach();
        void OnUpdate();
        void OnImGuiRender();

        void UTIL_ColorThing(const char *label, int target);

        // -- RUNTIME --
        enum SceneState
        {
            SceneStatePlay,
            SceneStateStop
        };
        SceneState currentSceneState;

        void StartSceneRuntime();
        void StopSceneRuntime();
        void UpdateRuntime();
        void UpdateEditor();
        // -------------

        // -- UI --
        void UI_RenderTopToolBar();
        void UI_RenderPlaySceneBar();
        // --------

        // -- SCENE --
        void OpenScene();
        void OpenScene(const std::string &name);
        void SaveSceneAs();
        void SaveScene();
        // -----------

        static void STATIC_EDITOR_UTIL_ResizeViewport(const Vector2 &viewport);
        static void STATIC_EDITOR_UTIL_MidSceneRender(Scene*active);

        static EditorLayer* GetInstance();
    };
}
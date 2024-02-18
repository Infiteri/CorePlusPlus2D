#pragma once

#include "Core.h"
#include "EditorSceneViewport.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Core
{
    struct CoreEditorViewportConfiguration : public ICoreEditorSceneViewportConfiguration
    {
        void MidSceneViewportRenderCall(Scene *scene);
    };

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
    };
}
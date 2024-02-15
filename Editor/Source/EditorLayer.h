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

    struct EditorState
    {
        EditorSceneViewport editorSceneViewport;
        SceneHierarchyPanel hierarchyPanel;

        std::string saveScenePath;
    };

    class EditorLayer : public Layer
    {
    public:
        EditorState state;

        EditorLayer();
        ~EditorLayer();

        void OnAttach();
        void OnImGuiRender();

        void UTIL_ColorThing(const char *label, int target);

        // -- UI --
        void UI_RenderTopToolBar();
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
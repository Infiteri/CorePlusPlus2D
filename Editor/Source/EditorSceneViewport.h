#pragma once

#include "Core.h"

namespace Core
{
    struct ICoreEditorSceneViewportConfiguration
    {
        void MidSceneViewportRenderCall(Scene *scene){};
    };

    class EditorSceneViewport
    {
    public:
        ICoreEditorSceneViewportConfiguration *EditorSceneConfig = nullptr;

        EditorSceneViewport(){};
        ~EditorSceneViewport(){};

        void RenderGUIDockspace();
        void RenderGUI();
        void RenderGUIDockspaceEnd();
    };
};
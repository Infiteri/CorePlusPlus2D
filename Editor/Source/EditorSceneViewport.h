#pragma once

#include "Core.h"

namespace Core
{
    class EditorSceneViewport
    {
    public:

        EditorSceneViewport(){};
        ~EditorSceneViewport(){};

        void RenderGUIDockspace();
        void RenderGUI();
        void RenderGUIDockspaceEnd();
    };
};
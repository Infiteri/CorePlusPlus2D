#pragma once

#include "Base.h"
#include "Buffer/FrameBuffer.h"
#include "Shader/Shader.h"
#include "Buffer/VertexArray.h"
#include "Renderer/Renderer.h"

namespace Core
{
    struct GPUScreen
    {
        Viewport *viewport;
        FrameBuffer *ScreenFramebuffer;
        VertexArray *ScreenVertexArray;
        Shader *ScreenShader;

        void Create();
        void EndGPUSideFrame();
        void DrawImageToScreen();
    };
}

#include "Renderer.h"
#include "Core/Memory/CeMemory.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture/TextureManager.h"
#include "Shader/Shader.h"
#include "Material/MaterialManager.h"
#include "Shader/ShaderSystem.h"
#include "Buffer/VertexArray.h"
#include "Screen.h"

#include "Core/Input.h"
#include "Core/Logger.h"

#include "Camera/OrthographicCamera.h"
#include "Camera/CameraSystem.h"

namespace Core
{
    struct RendererState
    {
        enum RenderingState
        {
            None,
            StartingFrame,
            RenderingScene,
            EndingFrame
        };

        RenderingState render_state;
        Viewport viewport{1024, 576};
        GPUScreen GPUscreen;
    };

    static RendererState *state;

    void RENDERER_UploadCameraDataToShader(Shader *s, Camera *c);

    void Renderer::Init()
    {
        {
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            state = new RendererState;
            state->render_state = RendererState::None;
        }

        //? Loading shaders
        {
            ShaderSystem::Load("EngineResources/Shaders/Object");
        }

        // Init GPU screen
        state->GPUscreen.viewport = &state->viewport; // ? Due to pointers, it will just work
        state->GPUscreen.Create();
        RegenerateObjectsWithNewViewport();

        // Init renderer sub systems
        CameraSystem::Init();
        CameraSystem::CreateOrthoCamera(1024, 576, "TestCamera");
        CameraSystem::Activate("TestCamera");

        TextureManager::Init();
        MaterialManager::Init();
    }

    void Renderer::Shutdown()
    {
        CameraSystem::Shutdown();
        TextureManager::Shutdown();
        MaterialManager::Shutdown();
    }

    FrameBuffer *Renderer::GetFrameBuffer()
    {
        return state->GPUscreen.ScreenFramebuffer;
    }

    void Renderer::BeginFrame()
    {
        state->render_state = RendererState::StartingFrame;

        state->GPUscreen.ScreenFramebuffer->Bind();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Render()
    {
        state->render_state = RendererState::RenderingScene;

        glClearColor(0.5, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CameraSystem::UpdateActiveCamera();

        //? Send camera data.
        RENDERER_UploadCameraDataToShader(ShaderSystem::Get("EngineResources/Shaders/Object"), CameraSystem::GetActiveAsOrtho());
    }

    void Renderer::EndFrame()
    {
        state->render_state = RendererState::EndingFrame;
        state->GPUscreen.EndGPUSideFrame();
    }

    void Renderer::DrawToScreen()
    {
        state->GPUscreen.DrawImageToScreen();
    }

    void Renderer::ResizeViewport(const Viewport &new_viewport)
    {
        if (!state)
            return;

        state->viewport = new_viewport;

        RegenerateObjectsWithNewViewport();
    }

    void Renderer::RegenerateObjectsWithNewViewport()
    {
        auto &vp = state->viewport;

        {
            auto active = CameraSystem::GetActiveAsOrtho();
            if (active)
                active->CalculateProjection(vp.width, vp.height);
        }

        {
            glViewport(0, 0, vp.width, vp.height);
            if (state->GPUscreen.ScreenFramebuffer)
                state->GPUscreen.ScreenFramebuffer->Resize(vp.width, vp.height);
        }
    }

    void Renderer::UploadTransform(const Matrix4 &transformMatrix)
    {
        auto s = ShaderSystem::Get("EngineResources/Shaders/Object");
        if (s)
            s->Mat4(transformMatrix, "uTransform");
    }

    void Renderer::UploadColor(const Color &color)
    {
        auto s = ShaderSystem::Get("EngineResources/Shaders/Object");
        if (s)
            s->Vec4(color.r / 255, color.g / 255, color.b / 255, color.a / 255, "uColor");
    }

    void Renderer::RenderVertexArray(VertexArray *array)
    {
        ShaderSystem::UseShaderIfExists("EngineResources/Shaders/Object");
        array->Bind();
        array->GetIndexBuffer()->Draw();
    }

    void Renderer::UploadTexture(Texture *text)
    {
        auto s = ShaderSystem::Get("EngineResources/Shaders/Object");
        if (s)
        {
            s->Use();
            text->Use();
            s->Int(text->GetIndex(), "uColorTexture");
        }
    }

    void RENDERER_UploadCameraDataToShader(Shader *s, Camera *c)
    {
        if (!s || !c)
            return;

        s->Mat4(c->GetProjection(), "uProjection");
        s->Mat4(c->GetView(), "uView");
    }
}
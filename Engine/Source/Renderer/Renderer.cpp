#include "Renderer.h"
#include "Core/Memory/CeMemory.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Buffer/FrameBuffer.h"
#include "Shader/Shader.h"
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

        Shader *ObjShader;
    };

    static RendererState *state;

    float data[] = {
        -100.5f, -100.5f, 0.0f,
        100.5f, -100.5f, 0.0f,
        0.0f, 100.5f, 0.0f};

    static VertexArray *vArray;

    void Renderer::Init()
    {
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        state = new RendererState;

        state->render_state = RendererState::None;

        // Init GPU screen
        state->GPUscreen.viewport = &state->viewport; // ? Due to pointers, it will just work
        state->GPUscreen.Create();
        RegenerateObjectsWithNewViewport();

        // Init renderer sub systems
        CameraSystem::Init();
        CameraSystem::CreateOrthoCamera(1024, 576, "TestCamera");
        CameraSystem::Activate("TestCamera");

        // TODO: Remove at some point
        state->ObjShader = new Shader("EngineResources/Shaders/Object.vs.glsl", "EngineResources/Shaders/Object.fs.glsl");
        vArray = new VertexArray();
        vArray->GenVertexBuffer(data, sizeof(data) * sizeof(float));
        vArray->GetVertexBuffer()->AddLayout(0, 0, 3);
        vArray->GetVertexBuffer()->Bind();
        vArray->Bind();
    }

    void Renderer::Shutdown()
    {
        CameraSystem::Shutdown();
    }

    void Renderer::BeginFrame()
    {
        state->render_state = RendererState::StartingFrame;

        state->GPUscreen.ScreenFramebuffer->Bind();
    }

    void Renderer::Render()
    {
        state->render_state = RendererState::RenderingScene;

        glClearColor(1, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CameraSystem::UpdateActiveCamera();
        state->ObjShader->Use();

        //? Send camera data.
        {
            auto active_camera = CameraSystem::GetActiveAsOrtho();
            if (active_camera)
            {
                state->ObjShader->Mat4(active_camera->GetProjection()->data, "uProjection");
                state->ObjShader->Mat4(active_camera->GetViewInverted().data, "uView");
            }
        }

        vArray->Bind();
        vArray->GetVertexBuffer()->Draw();
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

}
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Logger.h"
#include "Layer/LayerStack.h"

namespace Core
{
    static EngineState state;

    EngineState *Engine::GetState()
    {
        return &state;
    }

    void Engine::PreInit()
    {
        {
            LoggerInformation info;
            Logger::Init(info);
        }

        {
            WindowInformation window_info;
            window_info.x = 0;
            window_info.y = 0;
            window_info.width = 1920;
            window_info.height = 780;
            window_info.title = "What";
            state.window = new Window(window_info);
        }

        Renderer::Init();
        Renderer::ResizeViewport({state.window->GetWidth(), state.window->GetHeight()});
        LayerStack::Init();
    }

    void Engine::Init()
    {
    }

    bool Engine::ShouldRun()
    {
        return state.window->ShouldRun();
    }

    void Engine::Render()
    {
        Renderer::BeginFrame();
        Renderer::Render();
        Renderer::EndFrame();
        LayerStack::RenderImGui();
        Renderer::DrawToScreen();
    }

    void Engine::Update()
    {
        LayerStack::Update();
        state.window->Update();
    }

    void Engine::Shutdown()
    {
        delete state.window;
    }
}
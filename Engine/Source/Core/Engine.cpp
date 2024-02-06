#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Logger.h"
#include "IDManager.h"
#include "Layer/LayerStack.h"
#include "GLFW/glfw3.h"

namespace Core
{
    static EngineState state;
    static EngineDeltaTimeHolder timer;

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
        IDManager::Init();
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
        LayerStack::Render();
        Renderer::EndFrame();

        LayerStack::RenderImGui();
        Renderer::DrawToScreen();
    }

    void Engine::Update()
    {
        float time = (float)glfwGetTime();
        timer.delta = timer.last - time;
        timer.last = time;

        LayerStack::Update();
        state.window->Update();
    }

    void Engine::Shutdown()
    {
        delete state.window;
    }

    float Engine::GetDeltaTime()
    {
        return timer.delta;
    }
}
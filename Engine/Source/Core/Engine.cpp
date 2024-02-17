#include "Engine.h"
#include "Platform/Platform.h"
#include "Renderer/Renderer.h"
#include "Logger.h"
#include "IDManager.h"
#include "Layer/LayerStack.h"
#include "Layer/ImGuiLayer.h"
#include "Scene/World.h"

#include <GLFW/glfw3.h>

namespace Core
{
    static EngineState state;
    static EngineDeltaTimeHolder timer;
    static EngineConfiguration *config;
    static DynamicLibrary lib;

    void Engine::FeedConfigurationInEngine(EngineConfiguration *cfg)
    {
        config = cfg;
    }

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

        IDManager::Init();
        {
            WindowInformation window_info;
            if (config)
            {
                window_info = config->WindowInformation;
            }
            else
            {
                window_info.x = 0;
                window_info.y = 0;
                window_info.width = 1280;
                window_info.height = 720;
                window_info.title = "Core Engine";
            }

            state.window = new Window(window_info);
        }

        Renderer::Init();
        Renderer::ResizeViewport({state.window->GetWidth(), state.window->GetHeight()});
        LayerStack::Init();
        ImGuiLayer::Init();
        World::Init();

        Platform::CreateDynamicLibrary(&lib, "TestLibrary.dll");
        Platform::LibraryLoadFunction(&lib, "TestStuff");

        typedef void (*GameInit)();
        GameInit f = (GameInit)lib.functions["TestStuff"]->pfn;
        f();
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
        World::RenderActiveScene();
        LayerStack::Render();
        Renderer::EndFrame();
        Renderer::DrawToScreen();

        ImGuiLayer::BeginFrame();
        LayerStack::RenderImGui();
        ImGuiLayer::EndFrame();
    }

    void Engine::Update()
    {
        float time = (float)glfwGetTime();
        timer.delta = timer.last - time;
        timer.last = time;

        LayerStack::Update();
        World::UpdateActiveScene();
        state.window->Update();
    }

    void Engine::Shutdown()
    {
        Renderer::Shutdown();
        Logger::Shutdown();
        World::Shutdown();
        ImGuiLayer::Shutdown();
        delete state.window;
    }

    Window *Engine::GetWindow()
    {
        return state.window;
    }

    float Engine::GetDeltaTime()
    {
        return timer.delta;
    }
}
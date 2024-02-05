#include "EngineLoop.h"
#include "Engine.h"

namespace Core
{
    EngineLoop::EngineLoop()
    {
        application = nullptr;
    }

    EngineLoop::~EngineLoop()
    {
        delete application;
    }

    void EngineLoop::FeedApplication(Application *app)
    {
        application = app;
    }

    void EngineLoop::PreInit()
    {
        if (!application)
            return;

        Engine::PreInit();
        application->PreInit();
    }

    void EngineLoop::Init()
    {
        if (!application)
            return;

        Engine::Init();
        application->Init();
        }

    void EngineLoop::Run()
    {
        if (!application)
            return;

        while (Engine::ShouldRun())
        {
            application->Update();
            Engine::Update();

            application->Render();
            Engine::Render();
        }
    }

    void EngineLoop::Shutdown()
    {
        if (!application)
            return;

        Engine::Shutdown();
        application->Shutdown();
    }
}
#pragma once

#include "Base.h"
#include "Window.h"

namespace Core
{
    struct EngineConfiguration
    {
        WindowInformation WindowInformation;
    };

    struct EngineState
    {
        Window *window;
    };

    struct EngineDeltaTimeHolder
    {
        float delta;
        float last;
    };

    class CE_API Engine
    {
    public:
        Engine(){};
        ~Engine(){};

        static void FeedConfigurationInEngine(EngineConfiguration* cfg);

        /// @brief If you do something stoopid u deserve the aftermath
        /// @return Engine state*
        static EngineState *GetState();
        static Window *GetWindow();

        static void PreInit();
        static void Init();
        static bool ShouldRun();
        static void Render();
        static void Update();
        static void Shutdown();

        static float GetDeltaTime();
    };

}
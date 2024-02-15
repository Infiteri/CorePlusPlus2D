#pragma once

#include "Application.h"
#include "Window.h"
#include "EngineLoop.h"

extern Core::Application *Core::CreateApplication(Core::EngineConfiguration *cfg);

int main(int argc, char const *argv[])
{
    Core::EngineLoop loop;
    Core::EngineConfiguration EConfig;
    EConfig.WindowInformation.x = 0;
    EConfig.WindowInformation.y = 0;
    EConfig.WindowInformation.width = 1024;
    EConfig.WindowInformation.height = 576;
    EConfig.WindowInformation.title = "Core Engine";
    EConfig.WindowInformation.acceptDefaultWindowResizeCallback = true;
    EConfig.WindowInformation.mode = Core::WindowSizeMode::Maximized;

    auto app = Core::CreateApplication(&EConfig);
    Core::Engine::FeedConfigurationInEngine(&EConfig);
    loop.FeedApplication(app);
    loop.PreInit();
    loop.Init();
    loop.Run();
    loop.Shutdown();

    return 0;
}

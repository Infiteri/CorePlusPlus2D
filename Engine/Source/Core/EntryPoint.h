#pragma once

#include "Application.h"
#include "EngineLoop.h"

extern Core::Application *Core::CreateApplication();

int main(int argc, char const *argv[])
{
    Core::EngineLoop loop;
    auto app = Core::CreateApplication();
    loop.FeedApplication(app);
    loop.PreInit();
    loop.Init();
    loop.Run();
    loop.Shutdown();

    return 0;
}

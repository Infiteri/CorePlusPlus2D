#pragma once

#include "Base.h"
#include "Application.h"

namespace Core
{
    class CE_API EngineLoop
    {
    private:
        Application *application;

    public:
        EngineLoop();
        ~EngineLoop();

        void FeedApplication(Application *app);

        void PreInit();
        void Init();
        void Run();
        void Shutdown();
    };
}

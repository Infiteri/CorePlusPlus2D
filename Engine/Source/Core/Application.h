#pragma once

#include "Base.h"
#include "Engine.h"

namespace Core
{
    class CE_API Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void PreInit(){};
        virtual void Init(){};
        virtual void Update(){};
        virtual void Render(){};
        virtual void Shutdown(){};
    };

    Application *CreateApplication(EngineConfiguration *config);
}
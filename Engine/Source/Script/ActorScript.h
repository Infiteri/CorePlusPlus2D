#pragma once

#include "Base.h"
#include "Scene/Actor.h"
#include "Scene/Scene.h"

namespace Core
{
    class CE_API ActorScript
    {
    protected:
        Actor *Owner;
        friend class ScriptEngine;
        friend class Scene;

    public:
        ActorScript(){};
        ~ActorScript(){};

        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnDestroy();
    };

}
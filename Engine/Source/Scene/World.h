#pragma once

#include "Base.h"
#include "Scene.h"

#include <string>

namespace Core
{
    class CE_API World
    {
    public:
        World(){};
        ~World(){};

        // -- CLASS METHODS --
        static void Init();
        static void Shutdown();
        // -------------------

        static Scene *CreateScene(const std::string &name);
        static void ActiveScene(const std::string &name);

        // SCENE ACTIVATIONS METHODS
        static void InitializeActiveScene();
        static void StartActiveScene();
        static void UpdateActiveScene();
        static void RenderActiveScene();
        static void StopActiveScene();
        static void DestroyActiveScene();
    };
}
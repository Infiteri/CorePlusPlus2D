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
        static Scene *Get(const std::string &name);
        static bool Has(const std::string &name);
        static Scene *GetActiveScene();
        static void ActiveScene(const std::string &name);
        static void Delete(const std::string &name);

        static void CopyToActive(Scene* scene);

        // SCENE ACTIVATIONS METHODS
        static void InitializeActiveScene();
        static void StartActiveScene();
        static void UpdateActiveScene();
        static void RenderActiveScene();
        static void StopActiveScene();
        static void DestroyActiveScene();
    };
}
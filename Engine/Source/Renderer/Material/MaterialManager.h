#pragma once

#include "Base.h"
#include "Material.h"
#include <string>

namespace Core
{
    struct MaterialReference
    {
        Material *material;
        int references;
    };

    class MaterialManager
    {
    public:
        MaterialManager(){};
        ~MaterialManager(){};

        static void Init();
        static void Shutdown();

        static Material *Get(const std::string &name);
        static Material *GetDefault();

        static void Release(const std::string &name);
    };
}
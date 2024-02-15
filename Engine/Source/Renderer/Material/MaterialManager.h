#pragma once

#include "Base.h"
#include "Material.h"
#include <string>

#define CE_DEFAULT_MATERIAL_NAME "CE_DEAFULT_MATERIAL_NAME_DO_NOT_NAME_YOUR_MATERIAL_THIS012854528754165465"
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
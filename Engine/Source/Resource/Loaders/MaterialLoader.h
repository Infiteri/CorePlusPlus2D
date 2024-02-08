#pragma once

#include "Base.h"
#include "Renderer/Material/Material.h"

namespace Core
{
    class CE_API MaterialLoader
    {
    public:
        MaterialLoader();
        ~MaterialLoader();

        static void ExposeConfigToFile(const std::string &filename, Material::Configuration* config);
        static Material::Configuration GetFromFile(const std::string &filename);
    };
}

#include "MaterialLoader.h"
#include "Core/Logger.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Core
{
    void MaterialLoader::ExposeConfigToFile(const std::string &filename, Material::Configuration *config)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Material";
        out << YAML::Value << filename.c_str(); // TODO: Debatable. REVIEW-ME
        out << YAML::Key << "Name" << YAML::Value << config->name.c_str();
        out << YAML::Key << "ColorTextureName" << YAML::Value << config->colorTextureName.c_str();
        out << YAML::EndMap;

        std::ofstream fout(filename);
        fout << out.c_str();

        CE_CORE_DEBUG("MaterialLoader: Successfully exposed config to file. (%s)", filename.c_str());
    }

    Material::Configuration MaterialLoader::GetFromFile(const std::string &filename)
    {
        Material::Configuration cfg;
        YAML::Node node = YAML::LoadFile(filename);
        if (!node)
        {
            CE_CORE_ERROR("MaterialLoader: Cannot load file '%s'", filename.c_str());
            return cfg;
        }

        cfg.name = node["Name"].as<std::string>();
        cfg.colorTextureName = node["ColorTextureName"].as<std::string>();

        return cfg;
    }
}
#include "MaterialLoader.h"
#include "Core/Logger.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Core
{
    static YAML::Emitter &operator<<(YAML::Emitter &out, Color *color)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << color->r << color->g << color->b << color->a << YAML::EndSeq;
        return out;
    }

    void MaterialLoader::ExposeConfigToFile(const std::string &filename, Material::Configuration *config)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Material";
        out << YAML::Value << filename.c_str(); // TODO: Debatable. REVIEW-ME
        out << YAML::Key << "Name" << YAML::Value << config->name.c_str();
        out << YAML::Key << "ColorTextureName" << YAML::Value << config->colorTextureName.c_str();
        out << YAML::Key << "Color" << YAML::Value << &config->color;
        out << YAML::EndMap;

        std::ofstream fout(filename);
        fout << out.c_str();

        CE_CORE_DEBUG("MaterialLoader: Successfully exposed config to file. (%s)", filename.c_str());
    }

    Material::Configuration MaterialLoader::GetFromFile(const std::string &filename)
    {
        Material::Configuration cfg;
        std::ifstream stream(filename);
        if (!stream.good())
        {
            CE_CORE_ERROR("MaterialLoader: Failed to load material file. %s", filename.c_str());
            return cfg;
        }

        std::stringstream strStream(filename);
        strStream << stream.rdbuf();
        YAML::Node node = YAML::Load(strStream.str());
        if (!node)
        {
            CE_CORE_ERROR("MaterialLoader: Unable to load nodes for file (Wrong format) '%s'", filename.c_str());
            return cfg;
        }

        cfg.name = node["Name"].as<std::string>();
        cfg.colorTextureName = node["ColorTextureName"].as<std::string>();

        cfg.color = {
            node["Color"][0].as<float>(),
            node["Color"][1].as<float>(),
            node["Color"][2].as<float>(),
            node["Color"][3].as<float>()};
        return cfg;
    }
}
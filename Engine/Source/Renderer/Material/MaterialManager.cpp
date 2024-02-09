#include "MaterialManager.h"
#include "Resource/Loaders/MaterialLoader.h"
#include <unordered_map>

namespace Core
{
    static std::unordered_map<std::string, MaterialReference *> refs; // All material references

    static Material *defaultMaterial; // Default material

    void MaterialManager::Init()
    {
        defaultMaterial = new Material();
        defaultMaterial->SetName(CE_DEAFULT_MATERIAL_NAME);
    }

    void MaterialManager::Shutdown()
    {
        delete defaultMaterial;
    }

    Material *MaterialManager::Get(const std::string &name)
    {
        if (!refs[name])
        {
            refs[name] = new MaterialReference;
            refs[name]->references = 0;
            auto cfg = MaterialLoader::GetFromFile(name);
            refs[name]->material = new Material(&cfg);
        }

        refs[name]->references++;
        return refs[name]->material;
    }

    Material *MaterialManager::GetDefault()
    {
        return defaultMaterial;
    }

    void MaterialManager::Release(const std::string &name)
    {
        if (name == CE_DEAFULT_MATERIAL_NAME)
            return;

        refs[name]->references--;
        if (refs[name]->references == 0)
            delete refs[name]->material;
    }
}
#include "MaterialManager.h"
#include "Core/Logger.h"
#include "Resource/Loaders/MaterialLoader.h"
#include <unordered_map>

namespace Core
{
    static std::unordered_map<std::string, MaterialReference *> refs; // All material references

    static Material *defaultMaterial; // Default material

    void MaterialManager::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Material Manager", "CE_MAT_MAN");

        defaultMaterial = new Material();
        defaultMaterial->SetName(CE_DEFAULT_MATERIAL_NAME);
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

            CE_LOG("CE_MAT_MAN", Trace, "Material created: %s. (%i)", name.c_str(), refs[name]->references);
        }

        for (auto &it : refs)
        {
            auto thing = refs[it.first]->material;
            CE_LOG("CE_MAT_MAN", Info, "Material: %s", thing->GetName().c_str());
        }

        refs[name]->references++;
        CE_LOG("CE_MAT_MAN", Trace, "Material found: %s. (%i)", name.c_str(), refs[name]->references);
        return refs[name]->material;
    }

    Material *MaterialManager::GetDefault()
    {
        return defaultMaterial;
    }

    void MaterialManager::Release(const std::string &name)
    {
        if (name == CE_DEFAULT_MATERIAL_NAME)
            return;

        if (!refs[name])
        {
            CE_LOG("CE_MAT_MAN", Error, "No material found: %s.", name.c_str());
            return;
        }

        refs[name]->references--;
        CE_LOG("CE_MAT_MAN", Trace, "Material found, when releasing: %s. (%i)", name.c_str(), refs[name]->references);

        if (refs[name]->references == 0)
        {
            CE_LOG("CE_MAT_MAN", Trace, "Material found, getting deleted: %s. (%i)", name.c_str(), refs[name]->references);
            delete refs[name]->material;
            refs.erase(name);
        }
    }
}
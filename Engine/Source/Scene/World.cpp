#include "World.h"
#include "Core/Logger.h"
#include <unordered_map>

#define CE_CALL_METHOD_UTIL(name) \
    if (!activeScene)             \
        return;                   \
    activeScene->name()

namespace Core
{

    static std::unordered_map<std::string, Scene *> scenes;
    static Scene *activeScene;

    void World::Init()
    {
        CE_DEFINE_LOG_CATEGORY("World", "WORLD");
    }

    void World::Shutdown()
    {
        auto it = scenes.begin();
        while (it != scenes.end())
        {
            delete it->second;
            it++;
        }

        scenes.clear();
        activeScene = nullptr;
    }

    Scene *World::CreateScene(const std::string &name)
    {
        if (scenes[name] != nullptr)
        {
            CE_LOG("WORLD", Warn, "Scene '%s' already exists.", name.c_str());
            return scenes[name];
        }

        scenes[name] = new Scene(); // TODO: De-Serialize from file
        return scenes[name];
    }

    Scene *World::Get(const std::string &name)
    {
        return scenes[name];
    }

    bool World::Has(const std::string &name)
    {
        return scenes[name] != nullptr;
    }

    Scene *World::GetActiveScene()
    {
        return activeScene;
    }

    void World::ActiveScene(const std::string &name)
    {
        if (scenes[name] == nullptr)
        {
            CE_LOG("WORLD", Error, "Scene '%s' doesn't exists.", name.c_str());
            activeScene = nullptr;
        }

        activeScene = scenes[name];
        InitializeActiveScene();
    }

    void World::Delete(const std::string &name)
    {
        Scene *scene = scenes[name];
        if (scene)
        {
            auto it = scenes.find(name);
            scenes.erase(it);
            delete scene;
            scene = nullptr;
        }
    }

    void World::InitializeActiveScene()
    {
        CE_CALL_METHOD_UTIL(Init);
    }

    void World::StartActiveScene()
    {
        CE_CALL_METHOD_UTIL(Start);
    }

    void World::UpdateActiveScene()
    {
        CE_CALL_METHOD_UTIL(Update);
    }

    void World::RenderActiveScene()
    {
        CE_CALL_METHOD_UTIL(Render);
    }

    void World::StopActiveScene()
    {
        CE_CALL_METHOD_UTIL(Stop);
    }

    void World::DestroyActiveScene()
    {
        CE_CALL_METHOD_UTIL(Destroy);
    }
}
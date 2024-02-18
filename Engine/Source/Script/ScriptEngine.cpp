#include "ScriptEngine.h"
#include <unordered_map>

namespace Core
{
    static DynamicLibrary library;
    static std::unordered_map<std::string, ActorScript *> actorScripts;

    typedef ActorScript *(*GetActorScriptPFN)();

    void ScriptEngine::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Script Engine", "CE_SCRIPT");
        CE_LOG("CE_SCRIPT", Info, "Initialized.");
    }

    void ScriptEngine::StartRuntime()
    {
        for (auto a : actorScripts)
        {
            a.second->OnStart();
        }
    }

    void ScriptEngine::UpdateRuntime()
    {
        for (auto a : actorScripts)
        {
            a.second->OnUpdate();
        }
    }

    void ScriptEngine::StopRuntime()
    {
        for (auto a : actorScripts)
        {
            a.second->OnDestroy();
        }

        ClearScriptList();
    }

    void ScriptEngine::ClearScriptList()
    {
        for (auto a : actorScripts)
            delete a.second;

        actorScripts.clear();
    }

    void ScriptEngine::Shutdown()
    {
        CE_LOG("CE_SCRIPT", Info, "Shutdown.");
    }

    void ScriptEngine::RegisterScript(const std::string &name, const std::string &className, Actor *parent)
    {
        if (!library.Valid)
        {
            CE_LOG("CE_SCRIPT", Error, "Library not valid. (%s)", library.Name.c_str());
            return;
        }

        auto pfn = Platform::LibraryGetFunction<GetActorScriptPFN>(&library, className + "Create");
        RegisterScript(name, pfn(), parent);
    }

    void ScriptEngine::RegisterScript(const std::string &name, ActorScript *a, Actor *parent)
    {
        if (!a || !parent)
        {
            CE_LOG("CE_SCRIPT", Error, "Parent or script class not present");
            return;
        }

        a->Owner = parent;
        actorScripts[name] = a;
    }

    void ScriptEngine::LoadLibrary(const std::string &name)
    {
        Platform::CreateDynamicLibrary(&library, name);

        if (!library.Valid)
            CE_LOG("CE_SCRIPT", Fatal, "Unable to load library: %s.", name.c_str());
    }

    DynamicLibrary *ScriptEngine::GetLibrary()
    {
        return &library;
    }
}
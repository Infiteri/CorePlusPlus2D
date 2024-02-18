#pragma once

#include "Base.h"
#include "ActorScript.h"
#include "Platform/Platform.h"

namespace Core
{
    class ScriptEngine
    {
    public:
        ScriptEngine(){};
        ~ScriptEngine(){};

        static void Init();
        static void StartRuntime();
        static void UpdateRuntime();
        static void StopRuntime();
        static void ClearScriptList();
        static void Shutdown();

        // -- REGISTER --
        static void RegisterScript(const std::string &name, const std::string& className, Actor *parent);
        static void RegisterScript(const std::string &name, ActorScript *a, Actor *parent);
        // --------------

        static void
        LoadLibrary(const std::string &name);
        static DynamicLibrary *GetLibrary();
    };
}
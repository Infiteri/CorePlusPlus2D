#include "Scene.h"
#include "Script/ScriptEngine.h"

namespace Core
{
    Scene::Scene()
    {
        state = State::Uninitialized;
    }

    Scene::~Scene()
    {
        Destroy();
    }

    void Scene::Init()
    {
        for (auto a : actors)
            a->Init();

        state = State::Initialized;
    }

    void Scene::Start()
    {
        for (auto a : actors)
        {
            a->Start();

            // ? Register the script component on each actor
            {
                auto script = a->GetComponent<ActorScriptComponent>();
                if (script)
                    ScriptEngine::RegisterScript(a->GetName(), script->ClassName, a);
            }
        }

        ScriptEngine::StartRuntime();

        state = State::Started;
    }

    void Scene::Update()
    {
        for (auto a : actors)
            a->Update();

        ScriptEngine::UpdateRuntime();

        state = State::Running;
    }

    void Scene::Render()
    {
        for (auto a : actors)
            a->Render();

        state = State::Running;
    }

    void Scene::Stop()
    {
        for (auto a : actors)
            a->Stop();

        ScriptEngine::StopRuntime();

        state = State::Stopped;
    }

    void Scene::Destroy()
    {
        for (auto a : actors)
        {
            a->Destroy();
            delete a;
        }

        actors.clear();

        state = State::Destroyed;
    }

    void Scene::AddActor(Actor *a)
    {
        if (!a)
            return;

        actors.push_back(a);
    }

    Actor *Scene::AddActor()
    {
        return SpawnActor<Actor>();
    }
}
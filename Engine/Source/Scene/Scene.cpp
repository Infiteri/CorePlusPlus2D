#include "Scene.h"
#include "Core/Engine.h"
#include "Script/ScriptEngine.h"
#include "Renderer/Camera/CameraSystem.h"

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

    Scene *Scene::Copy(Scene *other)
    {
        Scene *scene = new Scene();

        scene->SetName(other->GetName());
        scene->state = other->GetState();

        for (auto a : other->GetActors())
            scene->SpawnActor<Actor>()->From(a);

        return scene;
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

            // ? Register camera
            {
                auto camera = a->GetComponent<OrthographicCameraComponent>();
                if (camera)
                {
                    camera->Camera->CalculateProjection(Engine::GetWindow()->GetWidth(), Engine::GetWindow()->GetHeight());
                    CameraSystem::AddOrthographicCamera(camera->Camera, "SceneCamera");
                    CameraSystem::Activate("SceneCamera");
                }
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

        CameraSystem::EraseCamera("SceneCamera");

        ScriptEngine::StopRuntime();

        state = State::Stopped;
    }

    void Scene::Destroy()
    {
        for (auto a : actors)
        {
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
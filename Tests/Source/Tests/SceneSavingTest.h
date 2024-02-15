#pragma once

#include "Test.h"

class SceneSavingTest : public Core::Test
{
public:
    SceneSavingTest() : Test("Scene saving Test"){};
    ~SceneSavingTest(){};

    bool Run()
    {

        Core::Scene *scene = Core::World::CreateScene("TEST SCENE");
        auto a = scene->SpawnActor<Core::Actor>();
        a->SetName("Test Mesh Actor");
        auto m = a->AddComponent<Core::MeshComponent>();
        m->mesh->SetGeometry(new Core::SquareGeometry(100, 100));
        Core::World::ActiveScene("TEST SCENE");

        Core::World::StartActiveScene();

        Core::SceneSerializer serializer(Core::World::GetActiveScene());
        serializer.Serialize("Assets/Scenes/TestScene.ce_scene");

        std::string activeScenePath;

        // Opening
        {
            activeScenePath = "Assets/Scenes/TestScene.ce_scene";
            Core::SceneSerializer serialize{Core::World::GetActiveScene()};
            serialize.DeserializeAndCreateNew("Assets/Scenes/TestScene.ce_scene");
        }

        // Saving
        {
            Core::SceneSerializer serializer(Core::World::GetActiveScene());
            serializer.Serialize(activeScenePath);
        }

        // Re-Opening
        {
            Core::SceneSerializer serialize{Core::World::GetActiveScene()};
            serialize.DeserializeAndCreateNew("Assets/Scenes/TestScene.ce_scene");
        }

        return true;
    };
};

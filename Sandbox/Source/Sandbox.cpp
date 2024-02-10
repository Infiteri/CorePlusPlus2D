#include "Core.h"
#include <imgui.h>
#include "Core/EntryPoint.h"

using namespace Core;

class SandboxLayer : public Layer
{
public:
    SandboxLayer(){};
    ~SandboxLayer(){};

    void OnAttach()
    {
        Scene *scene = World::CreateScene("New_Scene");
        auto a = scene->SpawnActor<Actor>();
        auto m = a->AddComponent<MeshComponent>();
        m->mesh->SetGeometry(new SquareGeometry(100, 100));
        World::ActiveScene("New_Scene");

        World::StartActiveScene();
    };

    void OnImGuiRender(){};
};

class Sandbox : public Application
{
public:
    Sandbox(){};
    ~Sandbox(){};

    void Init()
    {
        LayerStack::PushLayer(new SandboxLayer());
    };
};

Application *Core::CreateApplication()
{
    return new Sandbox();
};
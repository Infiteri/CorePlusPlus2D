#include "Core.h"
#include <imgui.h>
#include "Core/EntryPoint.h"

using namespace Core;

static Core::Mesh *mesh;
class SandboxLayer : public Layer
{
public:
    SandboxLayer(){};
    ~SandboxLayer(){};

    void OnAttach()
    {
        mesh = new Mesh();
        mesh->GetTransform()->Position.Set(100, 100, 0);
        mesh->SetGeometry(new SquareGeometry(100, 100));
    };

    void OnImGuiRender()
    {
        if (!mesh)
            return;

        ImGui::Begin("A");

        Transform *t = mesh->GetTransform();
        float data[3] = {t->Position.x, t->Position.y, t->Position.z};
        if (ImGui::DragFloat3("Position", data, 0.1))
        {
            t->Position.x = data[0];
            t->Position.y = data[1];
            t->Position.z = data[2];
        }

        ImGui::End();
    };

    void OnRender()
    {
        mesh->Render();
    };
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
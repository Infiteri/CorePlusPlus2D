#include "Core.h"
#include "Core/EntryPoint.h"

using namespace Core;

float data[] = {
    -250.5f, -250.5f, 0.0f, 0.0f, 0.0f,
    250.5f, -250.5f, 0.0f, 1.0f, 0.0f,
    250.5f, 250.5f, 0.0f, 1.0f, 1.0f,
    -250.0f, 250.5f, 0.0f, 0.0f, 1.0f};

CeU32 indices[] = {0, 1, 2, 2, 3, 0};

static Shader *ObjShader;
static VertexArray *vArray;

static Vector2 position{500, 500};

static Texture *text;

class SandboxLayer : public Layer
{
public:
    SandboxLayer(){};
    ~SandboxLayer(){};

    void OnAttach()
    {
        ObjShader = ShaderSystem::Get("EngineResources/Shaders/Object");
        vArray = new VertexArray();
        vArray->GenVertexBuffer(data, sizeof(data) * sizeof(float));
        vArray->GetVertexBuffer()->AddLayout(0, 0, 3);
        vArray->GetVertexBuffer()->AddLayout(1, 3, 2);
        vArray->GetVertexBuffer()->Bind();
        vArray->GenIndexBuffer(indices, sizeof(indices) * sizeof(CeU32));
        vArray->GetIndexBuffer()->Bind();
        vArray->Bind();

        text = new Texture("EngineResources/Images/Icons/folder.png");
    };

    void OnRender()
    {
        Renderer::UploadTexture(text);
        Renderer::UploadColor({0, 1, 0, 1});
        Renderer::UploadTransform(Matrix4::TranslateVec2(position));
        Renderer::RenderVertexArray(vArray);
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
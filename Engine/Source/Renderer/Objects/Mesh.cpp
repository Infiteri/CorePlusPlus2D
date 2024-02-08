#include "Mesh.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Material/MaterialManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture/TextureManager.h"

namespace Core
{
    static float data[] = {
        -100.5f, -100.5f, 0.0f, 0.0f, 0.0f,
        100.5f, -100.5f, 0.0f, 1.0f, 0.0f,
        100.5f, 100.5f, 0.0f, 1.0f, 1.0f,
        -100.0f, 100.5f, 0.0f, 0.0f, 1.0f};

    static CeU32 indices[] = {0, 1, 2, 2, 3, 0};

    Mesh::Mesh()
    {
        VArray = new VertexArray();
        VArray->GenVertexBuffer(data, sizeof(data) * sizeof(float));
        VArray->GetVertexBuffer()->AddLayout(0, 0, 3);
        VArray->GetVertexBuffer()->AddLayout(1, 3, 2);
        VArray->GetVertexBuffer()->Bind();
        VArray->GenIndexBuffer(indices, sizeof(indices) * sizeof(CeU32));
        VArray->GetIndexBuffer()->Bind();
        VArray->Bind();

        material = MaterialManager::Get("EngineResources/Materials/Test.ce_mat");
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::Render()
    {
        material->Use();
        Renderer::UploadTransform(transform.GetTransformMatrix());
        Renderer::RenderVertexArray(VArray);
    }
}
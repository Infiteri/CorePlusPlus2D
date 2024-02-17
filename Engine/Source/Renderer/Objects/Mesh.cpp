#include "Mesh.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Material/MaterialManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture/TextureManager.h"

namespace Core
{
    Mesh::Mesh()
    {
        VArray = nullptr;
        geometry = new Geometry();
        InitVertexArray();

        isMaterialUnique = false;
        material = MaterialManager::GetDefault();
    }

    Mesh::~Mesh()
    {
        MaterialManager::Release(material->GetName());

        if (VArray)
            delete VArray;

        if (geometry)
            delete geometry;
    }

    void Mesh::InitVertexArray()
    {
        if (!geometry)
            return;

        if (VArray != nullptr)
        {
            delete VArray;
            VArray = nullptr;
        }

        auto vertices = geometry->GetVertices();
        auto indices = geometry->GetIndices();

        VArray = new VertexArray();
        VArray->GenVertexBuffer(vertices, geometry->GetVerticesSize());
        VArray->GetVertexBuffer()->AddLayout(0, 0, 3);
        VArray->GetVertexBuffer()->AddLayout(1, 3, 2);
        VArray->GetVertexBuffer()->Bind();
        VArray->GenIndexBuffer(indices, geometry->GetIndicesSize());
        VArray->GetIndexBuffer()->Bind();
        VArray->Bind();
    }

    void Mesh::Render()
    {
        material->Use();
        Renderer::RenderVertexArray(VArray);
    }

    void Mesh::SetMaterial(const std::string &filename)
    {
        if (material && material->GetName() == filename)
            return;

        isMaterialUnique = false;
        if (material && material->GetName() != CE_DEFAULT_MATERIAL_NAME)
            MaterialManager::Release(material->GetName());

        material = MaterialManager::Get(filename);
    }

    void Mesh::SetMaterial(Material::Configuration *config)
    {
        if (material && !isMaterialUnique && material->GetName() != CE_DEFAULT_MATERIAL_NAME)
        {
            MaterialManager::Release(material->GetName());
            material = nullptr;
        }

        isMaterialUnique = true;
        material = new Material(config);
    }

    void Mesh::SetGeometry(Geometry *_geometry)
    {
        if (geometry)
            delete geometry;

        geometry = _geometry;
        InitVertexArray();
    }
}
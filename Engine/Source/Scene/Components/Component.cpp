#include "Component.h"
#include "Scene/Actor.h"

namespace Core
{
    MeshComponent::MeshComponent()
    {
        mesh = new Mesh();
    }

    void MeshComponent::Start()
    {
    }

    void MeshComponent::Render()
    {
        if (!mesh)
            return;

        mesh->Render();
    }

    void MeshComponent::Destroy()
    {
        if (mesh)
            delete mesh;

        mesh = nullptr;
    }
}
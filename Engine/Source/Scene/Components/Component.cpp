#include "Component.h"
#include "Scene/Actor.h"

namespace Core
{
    MeshComponent::MeshComponent()
    {
        mesh = new Mesh();
    }

    void MeshComponent::From(MeshComponent *other)
    {
        // ? Material
        {
            auto tMat = mesh->GetMaterial();
            auto oMat = other->mesh->GetMaterial();

            if (other->mesh->IsMaterialUnique())
            {
                tMat->GetColor()->Set(oMat->GetColor()->r, oMat->GetColor()->g, oMat->GetColor()->b, oMat->GetColor()->a);
                tMat->SetName(oMat->GetName());
                tMat->SetColorTexture(oMat->GetColorTexture()->GetImageName());
            }
            else
            {
                mesh->SetMaterial(oMat->GetName());
            }
        }

        //? Geometry
        {
            auto oGeo = other->mesh->GetGeometry();
            if (oGeo->GetType() == Geometry::Square)
            {
                auto square = (SquareGeometry *)oGeo;
                mesh->SetGeometry(new SquareGeometry(square->Width, square->Height));
            }
        }
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

    void ActorScriptComponent::From(ActorScriptComponent *other)
    {
        ClassName = other->ClassName;
    }

    OrthographicCameraComponent::OrthographicCameraComponent()
    {
        Camera = new OrthographicCamera(1024, 576); // Will be changed in scene startup
    }

    void OrthographicCameraComponent::SetOriginPoint(OrthographicCamera::OriginPoint point)
    {
        Camera->SetOriginPoint(point);
    }

    void OrthographicCameraComponent::Destroy()
    {
        delete Camera;
    }

    void OrthographicCameraComponent::Update()
    {
        Camera->GetPosition()->Set(&Owner->GetTransform()->Position);
    }

    void OrthographicCameraComponent::From(OrthographicCameraComponent *other)
    {
        Camera->SetOriginPoint(other->Camera->GetOriginPoint());
    }
}
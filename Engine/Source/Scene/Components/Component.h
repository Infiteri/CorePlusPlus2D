#pragma once

#include "Base.h"
#include "Renderer/Camera/OrthographicCamera.h"
#include "Renderer/Objects/Mesh.h"

namespace Core
{
    class Actor;

    class CE_API Component
    {
    public:
        Actor *Owner;

        Component(){};
        ~Component()
        {
            Destroy();
        };

        virtual void Init(){};
        virtual void Start(){};
        virtual void Update(){};
        virtual void Render(){};
        virtual void Stop(){};
        virtual void Destroy(){};

        virtual void From(Component *other){};
    };

    class CE_API MeshComponent : public Component
    {
    public:
        Mesh *mesh;

        MeshComponent();

        void From(MeshComponent *other);

        void Start();
        void Render();
        void Destroy();
    };

    class CE_API ActorScriptComponent : public Component
    {
    public:
        std::string ClassName;

        ActorScriptComponent(){};
        void From(ActorScriptComponent *other);
    };

    class CE_API OrthographicCameraComponent : public Component
    {
    public:
        OrthographicCamera *Camera;

        OrthographicCameraComponent();

        void SetOriginPoint(OrthographicCamera::OriginPoint point);

        void Destroy();
        void Update();

        void From(OrthographicCameraComponent *other);
    };
}
#pragma once

#include "Base.h"
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
    };

    class CE_API MeshComponent : public Component
    {
    public:
        Mesh *mesh;

        MeshComponent();

        void Start();
        void Render();
        void Destroy();
    };
}
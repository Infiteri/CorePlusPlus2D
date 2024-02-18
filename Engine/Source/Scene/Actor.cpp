#include "Actor.h"
#include "Renderer/Renderer.h"

#define CE_COPY_COMPONENT_UTIL(type)             \
    auto comp_##type = a->GetComponent<type>();  \
    if (comp_##type)                             \
    {                                            \
        AddComponent<type>()->From(comp_##type); \
    }

namespace Core
{
    Actor::Actor()
    {
        state = Uninitialized;
    }

    Actor::~Actor()
    {
        Destroy();
    }

    void Actor::From(Actor *a)
    {
        SetName(a->GetName());
        SetUUID(a->GetUUID()->Get());

        GetTransform()->Position.Set(&a->GetTransform()->Position);
        GetTransform()->Rotation.Set(&a->GetTransform()->Rotation);
        GetTransform()->Scale.Set(&a->GetTransform()->Scale);

        CE_COPY_COMPONENT_UTIL(MeshComponent);
        CE_COPY_COMPONENT_UTIL(ActorScriptComponent);
        CE_COPY_COMPONENT_UTIL(OrthographicCameraComponent);
    }

    void Actor::Init()
    {
        state = Initialized;

        for (Component *c : components)
        {
            c->Init();
        }
    }

    void Actor::Start()
    {
        state = Started;

        for (Component *c : components)
        {
            c->Start();
        }
    }

    void Actor::Update()
    {
        state = Running;

        for (Component *c : components)
        {
            c->Update();
        }
    }

    void Actor::Render()
    {
        state = Running;

        Renderer::UploadTransform(transform.GetTransformMatrix());

        for (Component *c : components)
        {
            c->Render();
        }
    }

    void Actor::Stop()
    {
        state = Stopped;

        for (Component *c : components)
        {
            c->Stop();
        }
    }

    void Actor::Destroy()
    {
        state = Destroyed;

        for (Component *c : components)
            delete c;

        components.clear();
    }

    void Actor::SetUUID(UUID uuid)
    {
        this->uuid = {uuid.Get()};
    }
}
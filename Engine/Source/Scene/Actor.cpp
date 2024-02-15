#include "Actor.h"
#include "Renderer/Renderer.h"

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
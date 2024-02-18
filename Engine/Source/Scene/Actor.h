#pragma once

#include "Base.h"
#include "Math/Transform.h"
#include "Components/Component.h"
#include "Core/UUID.h"

#include <string>
#include <vector>

namespace Core
{
    class CE_API Actor
    {
    public:
        enum State
        {
            Uninitialized,
            Initialized,
            Started,
            Running, /// @brief Both Rendering and Updating.
            Stopped,
            Destroyed /// @brief How?
        };

    private:
        std::string name;
        State state;
        std::vector<Component *> components;
        UUID uuid;
        Transform transform;

    public:
        Actor();
        ~Actor();

        void Init();
        void Start();
        void Update();
        void Render();
        void Stop();
        void Destroy();

        void From(Actor* a);

        inline State GetState() { return state; };

        inline std::string GetName() { return name; };
        void SetName(std::string nName) { name = nName; };

    inline UUID *GetUUID() { return &uuid; };
    void SetUUID(UUID uuid);
    inline Transform *GetTransform() { return &transform; };

        // -- COMPONENTS --
        template <typename T, typename... Args>
        T *AddComponent(Args... args)
        {
            T *comp = new T(args...);
            comp->Owner = this;

            if (state == Initialized)
                comp->Init();
            else if (state == Started)
            {
                comp->Init();
                comp->Start();
            }

            components.push_back(comp);
            return comp;
        };

        template <typename T>
        T *GetComponent()
        {
            for (Component *c : components)
            {
                T *typedComponent = dynamic_cast<T *>(c);
                if (typedComponent)
                {
                    return typedComponent;
                }
            }

            return nullptr;
        };

        template <typename T>
        bool HasComponent()
        {
            return GetComponent<T>() != nullptr;
        };

        template <typename T>
        void RemoveComponent()
        {
            for (auto it = components.begin(); it != components.end(); ++it)
            {
                T *typedComponent = dynamic_cast<T *>(*it);
                if (typedComponent)
                {
                    components.erase(it);
                    typedComponent->Destroy();
                    delete typedComponent;
                    break;
                }
            }
        };
        // ----------------
    };

}
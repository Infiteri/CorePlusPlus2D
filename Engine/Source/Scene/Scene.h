#pragma once

#include "Base.h"
#include "Actor.h"

#include <string>
#include <vector>

namespace Core
{
    class CE_API Scene
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
        std::vector<Actor *> actors;
        State state;

    public:
        Scene();
        ~Scene();

        void Init();
        void Start();
        void Update();
        void Render();
        void Stop();
        void Destroy();

        inline State GetState() { return state; };

        inline std::string GetName() { return name; };
        void SetName(std::string nName) { name = nName; };

        inline std::vector<Actor *> GetActors() { return actors; };
        Actor *AddActor();

        template <typename T>
        T *SpawnActor()
        {
            T *t = new T();
            actors.push_back(t);
            return t;
        };
    };
}
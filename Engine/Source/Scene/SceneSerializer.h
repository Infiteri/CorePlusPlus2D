#pragma once

#include "Base.h"
#include "Scene.h"
#include "Actor.h"

namespace YAML
{
    class Emitter;
};

namespace Core
{

    /// @brief Stack allocated object that serializes or deserializes a scene.
    class CE_API SceneSerializer
    {
    private:
        Scene *scene;

        void SerializeActor(Actor *a, YAML::Emitter &out);

    public:
        SceneSerializer(Scene *_scene);
        ~SceneSerializer();

        /// @brief Will serialize the passed-in scene at the constructor with a path
        /// @param name The path to serialize in.
        void Serialize(const std::string &name);

        /// @brief Will deserialize into passed-in scene at the constructor with a path.
        /// @param name The path to serialize in.
        void Deserialize(const std::string &name);

        void DeserializeAndCreateNew(const std::string &name);
    };
}
#include "SceneSerializer.h"
#include "Core/Logger.h"
#include "Renderer/Color.h"
#include "Math/Vectors.h"
#include "World.h"

#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>

#define CE_SER_FIELD(name, thing) out << YAML::Key << name << YAML::Value << thing;

namespace Core
{
    YAML::Emitter &operator<<(YAML::Emitter &out, Vector2 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Vector3 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << v->z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Vector4 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << v->z << v->w << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Color *color)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << color->r << color->g << color->b << color->a << YAML::EndSeq;
        return out;
    }

    void Vector3ToYAML(const std::string &name, Vector3 *v, YAML::Emitter &out)
    {
        out << YAML::Key << name.c_str() << YAML::Value << v;
    }

    void YAMLToVector3(YAML::Node node, Vector3 *o)
    {
        if (node)
            o->Set(node[0].as<float>(), node[1].as<float>(), node[2].as<float>());
        else
            o->Set(0, 0, 0);
    }

    void YAMLToColor(YAML::Node node, Color *o)
    {
        if (node)
            o->Set(node[0].as<float>(), node[1].as<float>(), node[2].as<float>(), node[3].as<float>());
        else
            o->Set(255, 255, 255, 255);
    }

    SceneSerializer::SceneSerializer(Scene *_scene)
    {
        CE_DEFINE_LOG_CATEGORY("Scene Serializer", "CE_SCN_SER");
        scene = _scene;
    }

    SceneSerializer::~SceneSerializer()
    {
    }

    void SceneSerializer::SerializeActor(Actor *a, YAML::Emitter &out)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Actor";
        out << YAML::Value << "Filed";

        out << YAML::Key << "UUID";
        out << YAML::Value << a->GetUUID()->Get();

        out << YAML::Key << "Name";
        out << YAML::Value << a->GetName().c_str();

        //? Serialize Transform
        {
            auto t = a->GetTransform();
            out << YAML::Key << "Transform";
            out << YAML::BeginMap;
            Vector3ToYAML("Position", &t->Position, out);
            Vector3ToYAML("Rotation", &t->Rotation, out);
            Vector3ToYAML("Scale", &t->Scale, out);
            out << YAML::EndMap;
        }

        //? Serialize the mesh component
        {
            auto m = a->GetComponent<MeshComponent>();
            if (m)
            {
                out << YAML::Key << "MeshComponent";
                out << YAML::BeginMap;
                {

                    out << YAML::Key << "Material";
                    out << YAML::BeginMap;
                    auto mat = m->mesh->GetMaterial();
                    if (m->mesh->IsMaterialUnique())
                    {
                        CE_SER_FIELD("IsMaterialUnique", "True");
                        CE_SER_FIELD("UniqueMaterialPath", m->mesh->GetMaterial()->GetName());
                    }
                    else
                    {
                        CE_SER_FIELD("IsMaterialUnique", "False");
                        CE_SER_FIELD("Color", mat->GetColor());
                        CE_SER_FIELD("ColorTexture", mat->GetColorTexture()->GetImageName());
                    }
                    out << YAML::EndMap;
                }

                {

                    out << YAML::Key << "Geometry";
                    out << YAML::BeginMap;
                    auto geo = m->mesh->GetGeometry();

                    switch (geo->GetType())
                    {
                    case Geometry::None:
                    default:
                        CE_SER_FIELD("Type", "None");
                        break;

                    case Geometry::Square:
                        auto b = (SquareGeometry *)geo;
                        CE_SER_FIELD("Type", "Square");
                        CE_SER_FIELD("Width", b->Width);
                        CE_SER_FIELD("Height", b->Height);
                        break;
                    }

                    out << YAML::EndMap;
                }

                out << YAML::EndMap;
            }
        }

        // ? Script component
        {
            auto s = a->GetComponent<ActorScriptComponent>();
            if (s)
            {

                out << YAML::Key << "ActorScriptComponent";
                out << YAML::BeginMap;
                CE_SER_FIELD("ClassName", s->ClassName.c_str());
                out << YAML::EndMap;
            }
        }

        out << YAML::EndMap;
    }

    void SceneSerializer::Serialize(const std::string &name)
    {
        if (!scene)
        {
            CE_ERROR("Passed-in scene is nullptr. (Serialize)");
            return;
        }

        if (name.empty())
        {
            CE_ERROR("Passed-in name empty. (Serialize)");
            return;
        }

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene";
        out << YAML::Value << scene->GetName().c_str();
        out << YAML::Key << "Actors";
        out << YAML::Value << YAML::BeginSeq;
        for (auto a : scene->GetActors())
            SerializeActor(a, out);
        out << YAML::EndSeq;

        out << YAML::EndMap;

        std::ofstream fout(name);
        fout << out.c_str();
    }

    void SceneSerializer::Deserialize(const std::string &name)
    {
        if (!scene)
        {
            CE_ERROR("Scene isn't present. (Deserialize)");
            return;
        }

        if (name.empty())
        {
            CE_ERROR("Passed-in name empty. (Deserialize)");
            return;
        }

        YAML::Node data = YAML::LoadFile(name);

        if (!data["Scene"])
        {
            CE_LOG("CE_SCN_SER", Error, "Scene file data isn't formatted correctly. (Serialize)");
            return;
        }

        std::string sceneName = data["Scene"].as<std::string>();
        scene->SetName(sceneName);

        auto actors = data["Actors"];
        if (actors)
        {
            for (auto actor : actors)
            {
                Actor *a = new Actor();
                a->SetUUID(actor["UUID"].as<CeU64>());
                a->SetName(actor["Name"].as<std::string>());

                //? Transform
                {
                    auto transform = actor["Transform"];
                    if (transform)
                    {
                        YAMLToVector3(transform["Position"], &a->GetTransform()->Position);
                        YAMLToVector3(transform["Rotation"], &a->GetTransform()->Rotation);
                        YAMLToVector3(transform["Scale"], &a->GetTransform()->Scale);
                    }
                    else
                        CE_LOG("CE_SCN_SER", Error, "No transform bound to actor. (Deserialize).");
                }

                //? MeshComponent
                {
                    auto mc = actor["MeshComponent"];
                    if (mc)
                    {
                        auto mesh = a->AddComponent<MeshComponent>();
                        auto mat = mc["Material"];
                        if (mat["IsMaterialUnique"].as<std::string>() == "True")
                        {
                            mesh->mesh->SetMaterial(mat["UniqueMaterialPath"].as<std::string>());
                        }
                        else
                        {
                            YAMLToColor(mat["Color"], mesh->mesh->GetMaterial()->GetColor());

                            mesh->mesh->GetMaterial()->SetColorTexture(mat["ColorTexture"].as<std::string>());
                        }

                        auto geo = mc["Geometry"];
                        if (geo["Type"].as<std::string>() == "Square")
                        {
                            mesh->mesh->SetGeometry(new SquareGeometry(geo["Width"].as<float>(), geo["Height"].as<float>()));
                        }
                        else
                        {
                        }
                    }
                }

                // ? ActorScriptComponent
                {
                    auto sc = actor["ActorScriptComponent"];
                    if (sc)
                    {
                        a->AddComponent<ActorScriptComponent>()->ClassName = sc["ClassName"].as<std::string>();
                    }
                }

                scene->AddActor(a);
            }
        }
    }

    void SceneSerializer::DeserializeAndCreateNew(const std::string &name)
    {
        World::StopActiveScene();
        std::ifstream stream(name);
        std::stringstream strStream(name);
        strStream << stream.rdbuf();
        YAML::Node data = YAML::Load(strStream.str());
        if (!data["Scene"])
            return;

        std::string sceneName = data["Scene"].as<std::string>();

        if (World::Get(sceneName) != nullptr)
            World::Delete(sceneName);

        World::CreateScene(sceneName);
        World::ActiveScene(sceneName);

        scene = World::GetActiveScene();
        Deserialize(name);
    }
}
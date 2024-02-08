#pragma once

#include "Base.h"
#include <string>
#include "Resource/Image.h"

namespace Core
{
    class CE_API Texture
    {
    public:
        struct Configuration
        {
        };

        enum Type
        {
            WhiteDefault,
            EmptyLoaded,
            ResourceLoaded
        };

    private:
        CeU32 id;
        CeU32 index;
        Image *image;
        Type type;

        Configuration config;

        bool loaded = false;

        void GenNewIndex();
        void SetupEmptyConfig();

        void LoadWithNeedConfig(int width, int height, CeU32 channels, CeU8 *data, Configuration *cfg);

    public:
        Texture();
        Texture(const std::string &filename);
        Texture(const std::string &filename, Configuration *config);
        ~Texture();

        void Destroy();

        void Load();
        void Load(const std::string &filename);
        void Load(const std::string &filename, Configuration *config);

        void Bind();
        void Unbind();
        void Use();

        inline Image *GetImage() { return image; };
        inline Configuration *GetConfig() { return &config; };
        inline CeU32 GetID() { return id; };
        inline CeU32 GetIndex() { return index; };

        void BindType(Type type);
        inline Type GetType() { return type; };

        std::string GetImageName();
    };

}
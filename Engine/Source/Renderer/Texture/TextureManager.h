#pragma once

#include "Base.h"
#include "Texture.h"
#include <string>
#include <unordered_map>

namespace Core
{
    class CE_API TextureManager
    {
    public:
        TextureManager(){};
        ~TextureManager(){};

        static void Init();
        static void Shutdown();

        static Texture *Get(const std::string &name);
        static Texture *Load(const std::string &name);
        static void Release(const std::string &name);

        static Texture *GetWhiteTexture();
    };
}
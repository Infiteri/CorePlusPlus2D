#pragma once

#include "Base.h"
#include "Renderer/Color.h"
#include "Renderer/Texture/Texture.h"
#include <string>

namespace Core
{
    class Material
    {
    public:
        struct Configuration
        {
            std::string name;
            std::string colorTextureName;
            Color color;
        };

    private:
        std::string name;
        Color color;
        Texture *colorTexture;

    public:
        Material();
        Material(Configuration *config);
        ~Material();

        void Use();

        void SetName(const std::string &newName) { name = newName; };

        void SetColorTexture(const std::string& name);

        inline Color *GetColor() { return &color; };
        inline Texture *GetColorTexture() { return colorTexture; };
        inline std::string GetName() { return name; };
    };
}
#include "Material.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture/TextureManager.h"

namespace Core
{
    Material::Material()
    {
        colorTexture = TextureManager::GetWhiteTexture();
        name = "";
        color = {255, 255, 255, 255};
    }

    Material::Material(Configuration *config)
    {
        name = config->name;
        colorTexture = TextureManager::Get(config->colorTextureName);
        color.Set(config->color.r, config->color.g, config->color.b, config->color.a);
    }

    Material::~Material()
    {
        if (colorTexture && colorTexture->GetType() != Texture::WhiteDefault)
            TextureManager::Release(colorTexture->GetImageName());
    }

    void Material::Use()
    {
        Renderer::UploadColor(color);
        Renderer::UploadTexture(colorTexture);
    }

    void Material::SetColorTexture(const std::string &name)
    {
        if (!name.empty())
        {
            if (colorTexture)
            {
                if (colorTexture->GetImageName() == name)
                {
                    return;
                }
                else if (colorTexture->GetType() != Texture::WhiteDefault)
                    TextureManager::Release(colorTexture->GetImageName());
            }
            colorTexture = nullptr;
            colorTexture = TextureManager::Get(name);
        }
        else
        {
            if (colorTexture && colorTexture->GetType() != Texture::WhiteDefault)
                TextureManager::Release(colorTexture->GetImageName());

            colorTexture = TextureManager::GetWhiteTexture();
        }
    }
}
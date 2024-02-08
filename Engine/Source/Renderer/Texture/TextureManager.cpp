#include "TextureManager.h"
#include "Core/Logger.h"

namespace Core
{
    struct TextureReference
    {
        Texture *texture;
        int references;
    };

    static std::unordered_map<std::string, TextureReference *> refs;
    static TextureReference whiteTextureRef;

    void TextureManager::Init()
    {
        whiteTextureRef.texture = new Texture();
        whiteTextureRef.texture->BindType(Texture::WhiteDefault);
    }

    void TextureManager::Shutdown()
    {
        for (auto it : refs)
            Release(it.first);

        delete whiteTextureRef.texture;
    }

    Texture *TextureManager::Get(const std::string &name)
    {
        if (name.empty())
            return whiteTextureRef.texture;

        if (!refs[name])
            Load(name);

        refs[name]->references++;
        return refs[name]->texture;
    }

    Texture *TextureManager::Load(const std::string &name)
    {
        if (!refs[name])
        {
            refs[name] = new TextureReference;
            refs[name]->texture = new Texture(name);
            refs[name]->references = 0;

            CE_CORE_TRACE("TextureManager: Loaded texture: %s.", name.c_str());
        }

        return refs[name]->texture;
    }

    void TextureManager::Release(const std::string &name)
    {
        refs[name]->references--;

        if (refs[name]->references <= 0)
        {
            delete refs[name]->texture;
            refs[name]->references = 0;
            refs.erase(name);

            CE_CORE_TRACE("TextureManager: Released texture: %s.", name.c_str());
        }
    }
    Texture *TextureManager::GetWhiteTexture()
    {
        whiteTextureRef.references++;
        return whiteTextureRef.texture;
    }
}
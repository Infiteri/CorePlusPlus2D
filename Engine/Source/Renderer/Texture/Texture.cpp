#include "Texture.h"
#include "Core/Logger.h"
#include "Core/IDManager.h"
#include <glad/glad.h>

namespace Core
{
    static GLenum IDToGLEnum(CeU32 id)
    {
        switch (id)
        {

        case 4:
            return GL_RGBA;
            break;

        default:
        case 3:
            return GL_RGB;
            break;
        }
    }

    void Texture::LoadWithNeedConfig(int width, int height, CeU32 channels, CeU8 *data, Configuration *cfg)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, IDToGLEnum(channels), width, height, 0, IDToGLEnum(channels), GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    void Texture::GenNewIndex()
    {
        index = IDManager::GetNewTextureIndex();
    }

    void Texture::SetupEmptyConfig()
    {
    }

    Texture::Texture()
    {
        Load();
    }

    Texture::Texture(const std::string &filename)
    {
        Load(filename);
    }

    Texture::Texture(const std::string &filename, Configuration *_config)
    {
        Load(filename, _config);
    }

    Texture::~Texture()
    {
        Destroy();
    }

    void Texture::Destroy()
    {
        if (image)
            delete image;
        image = nullptr;

        glDeleteTextures(1, &id);
        id = 0;
        index = 0;
        IDManager::RemoveOneFromTextureIndex();

        loaded = false;
    }

    void Texture::Load()
    {
        BindType(EmptyLoaded);
        Load("", nullptr);
    }

    void Texture::Load(const std::string &filename)
    {
        BindType(ResourceLoaded);
        Load(filename, nullptr);
    }

    void Texture::Load(const std::string &filename, Configuration *_config) // TODO: If _config is nullptr, use no config and make sure to use defaults. Users fault might warn in future. REVISE ME
    {
        CE_CORE_DEBUG("Created texture: %s", filename.c_str());
        if (loaded)
            Destroy();

        GenNewIndex();
        glGenTextures(1, &id);
        Bind();

        if (filename.empty())
        {
            image = nullptr;
            CeU8 data[4] = {255, 255, 255, 255};
            LoadWithNeedConfig(1, 1, 4, data, _config);
        }
        else
        {
            image = new Image(filename);
            LoadWithNeedConfig(image->GetWidth(), image->GetHeight(), image->GetChannels(), image->GetData(), _config);
            image->FreeData();
        }

        loaded = true;
    }

    void Texture::Load(CeU8 *data, float width, float height, int channels)
    {
        CE_CORE_DEBUG("Created texture: %i", width);
        if (loaded)
            Destroy();

        GenNewIndex();
        glGenTextures(1, &id);
        Bind();

        LoadWithNeedConfig(width, height, channels, data, nullptr);

        loaded = true;
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0 + index);
        Bind();
    }

    void Texture::BindType(Type _type)
    {
        type = _type;
    }

    std::string Texture::GetImageName()
    {
        if (image)
            return image->GetName();
        else
            return "";
    }

    int Texture::GetWidth()
    {
        if (!image)
            return 100;

        return image->GetWidth();
    }

    int Texture::GetHeight()
    {
        if (!image)
            return 100;

        return image->GetWidth();
    }
}
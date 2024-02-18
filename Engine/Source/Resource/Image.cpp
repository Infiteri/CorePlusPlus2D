#include "Image.h"
#include "Core/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Core
{
    Image::Image(const std::string &filename)
    {
        name = filename;
        width = height = channels = 0;
        data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
        if (!data)
        {
            CE_CORE_ERROR("Image::Image: '%s' image cannot be loaded.", filename.c_str());
        }
    }

    Image::~Image()
    {
        FreeData();
        data = nullptr;
        name.clear();
        width = height = channels = 0;
    }

    void Image::FreeData()
    {
        if (!data)
            return; // OK, the data was deleted earlier. (Happens in texture where FreeData is called in order to clear RAM and therefore no more data is present)

        stbi_image_free(data);
    }
}
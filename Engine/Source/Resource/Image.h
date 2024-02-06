#pragma once

#include "Base.h"
#include <string>

#define CE_IMAGE_INLINE_GETTER(type, name, ret) \
    inline type Get##name() { return ret; }

namespace Core
{
    /// @brief Pass a filename, get an image, thats it.
    class CE_API Image
    {
    private:
        std::string name;
        int width;
        int height;
        int channels;
        CeU8 *data;

    public:
        Image(const std::string &filename);
        ~Image();

        void FreeData();

        CE_IMAGE_INLINE_GETTER(std::string, Name, name);
        CE_IMAGE_INLINE_GETTER(int, Width, width);
        CE_IMAGE_INLINE_GETTER(int, Height, height);
        CE_IMAGE_INLINE_GETTER(int, Channels, channels);
        CE_IMAGE_INLINE_GETTER(CeU8 *, Data, data);
    };
}
#pragma once

#include "Base.h"

namespace Core
{
    class IDManager
    {
    public:
        IDManager(){};
        ~IDManager(){};

        static void Init();

        static int GetNewTextureIndex();
        static void RemoveOneFromTextureIndex();
    };
}
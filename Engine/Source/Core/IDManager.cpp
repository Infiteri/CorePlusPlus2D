#include "IDManager.h"
#include "Logger.h"

namespace Core
{
    static int TEXTURE_INDEX;

    void IDManager::Init()
    {
        TEXTURE_INDEX = -1;

        CE_CORE_DEBUG("IDManager: Initialized.");
    }

    int IDManager::GetNewTextureIndex()
    {
        TEXTURE_INDEX++;
        CE_CORE_DEBUG("IDManager: Post new-gen texture index: %i.", TEXTURE_INDEX);
        return TEXTURE_INDEX;
    }

    void IDManager::RemoveOneFromTextureIndex()
    {
        TEXTURE_INDEX--;

        CE_CORE_DEBUG("IDManager: Post subtract texture index: %i.", TEXTURE_INDEX);
    }
}
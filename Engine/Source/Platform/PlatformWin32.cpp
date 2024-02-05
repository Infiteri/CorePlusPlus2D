#include "Platform.h"

#ifdef CE_WIN32

#include "Core/Logger.h"
#include "Core/Engine.h"

#include <windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <commdlg.h>
#include <shlwapi.h>
#include <fstream>

namespace Core
{
    void Platform::SetConsoleColor(PlatformLogColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD colorAttribute = FOREGROUND_INTENSITY; // Default to high-intensity (bright) text

        switch (color)
        {
        case PlatformLogColor::White:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;

        case PlatformLogColor::Gray:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;

        case PlatformLogColor::Red:
            colorAttribute |= FOREGROUND_RED;
            break;

        case PlatformLogColor::DarkRed:
            colorAttribute |= FOREGROUND_RED;
            break;

        case PlatformLogColor::Blue:
            colorAttribute |= FOREGROUND_BLUE;
            break;

        case PlatformLogColor::Green:
            colorAttribute |= FOREGROUND_GREEN;
            break;

        case PlatformLogColor::Yellow:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN;
            break;

        default:
            // Default to white if an unsupported color is specified
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        }

        SetConsoleTextAttribute(hConsole, colorAttribute);
    }

    void Platform::LogMessage(const char *msg)
    {
        OutputDebugStringA(msg);

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD bytesWritten;

        WriteConsoleA(hConsole, msg, strlen(msg), &bytesWritten, NULL);
    }

    void *Platform::MemSet(void *block, int value, CeU64 size)
    {
        return memset(block, value, size);
    }

    void Platform::Free(void *block)
    {
        free(block);
    }

    void *Platform::Allocate(CeU64 size)
    {

        return malloc(size);
    }

    void *Platform::MemCpy(void *dest, const void *source, CeU64 size)
    {
        return memcpy(dest, source, size);
    }

    std::string Platform::ReadFileContent(const std::string &path)
    {
        std::string vertResult;
        std::ifstream inVert(path, std::ios::in | std::ios::binary);

        if (inVert)
        {

            inVert.seekg(0, std::ios::end);
            vertResult.resize(inVert.tellg());
            inVert.seekg(0, std::ios::beg);
            inVert.read(&vertResult[0], vertResult.size());
            inVert.close();
        }
        else
        {
            CE_CORE_ERROR("Unable to read file content:  %s", path.c_str());
            vertResult = "";
        }

        return vertResult;
    }
}

#endif
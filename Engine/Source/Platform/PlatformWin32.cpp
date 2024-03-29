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

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

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

    // -- Library --
    bool Platform::CreateDynamicLibrary(DynamicLibrary *lib, const std::string &name)
    {
        lib->Valid = false;
        lib->Internal = 0;
        lib->Name = name;

        HMODULE mod = LoadLibrary(name.c_str());
        if (mod == NULL)
        {
            CE_CORE_ERROR("Platform: Loading library '%s' wasn't successful.", name.c_str());

            lib->Valid = false;
            return false;
        }

        lib->Internal = mod;
        lib->Valid = true;

        return true;
    }

    bool Platform::LibraryLoadFunction(DynamicLibrary *library, const std::string &functionName)
    {
        if (!library || !library->Valid)
            return false;

        FARPROC f_addr = GetProcAddress((HMODULE)library->Internal, functionName.c_str());
        if (!f_addr)
            return false;

        DynamicLibraryFunction *f = new DynamicLibraryFunction;
        f->pfn = (void *)f_addr;
        f->name = functionName;
        library->functions[functionName] = f;

        return true;
    }

    void Platform::DestroyDynamicLibrary(DynamicLibrary *lib)
    {
        if (!lib || !lib->Valid)
        {
            CE_CORE_WARN("Platform: Unloading cannot be done on library, not valid or nullptr.");
            return;
        }

        for (auto it = lib->functions.begin(); it != lib->functions.end(); it++)
            delete it->second;

        lib->functions.clear();

        FreeLibrary((HMODULE)lib->Internal);
    }
    // -- Library --

    std::string Platform::OpenFileDialog(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        CHAR currentDir[256] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *)Engine::GetWindow()->GetHandle());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;

        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            // Calculate the relative path from the current directory
            std::string fullPath = ofn.lpstrFile;
            std::string currentDirectory = currentDir;
            if (fullPath.find(currentDirectory) == 0)
            {
                // Remove the current directory from the full path to get the relative path
                std::string relativePath = fullPath.substr(currentDirectory.length() + 1);
                return relativePath;
            }
        }

        return std::string();
    }

    std::string Platform::SaveFileDialog(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        CHAR currentDir[256] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *)Engine::GetWindow()->GetHandle());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

        // Sets the default extension by extracting it from the filter
        ofn.lpstrDefExt = strchr(filter, '\0') + 1;

        if (GetSaveFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;

        return std::string();
    }

    std::vector<std::string> Platform::GetFilePathsInDirectory(const std::string &directoryPath)
    {
        std::vector<std::string> filePaths;

        WIN32_FIND_DATA findData;
        HANDLE hFind = FindFirstFile((directoryPath + "/*").c_str(), &findData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            return filePaths;
        }

        do
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                filePaths.push_back(directoryPath + "/" + findData.cFileName);
            }
        } while (FindNextFile(hFind, &findData));

        FindClose(hFind);

        return filePaths;
    }

    std::vector<std::string> Platform::GetFolderPathsInDirectory(const std::string &directoryPath)
    {
        std::vector<std::string> folderNames;

        WIN32_FIND_DATA findData;
        HANDLE hFind = FindFirstFile((directoryPath + "/*").c_str(), &findData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            return folderNames;
        }

        do
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                std::string folderName = findData.cFileName;
                if (folderName != "." && folderName != "..")
                {
                    folderNames.push_back(folderName);
                }
            }
        } while (FindNextFile(hFind, &findData));

        FindClose(hFind);

        return folderNames;
    }

    std::vector<DirectoryEntry> Platform::GetDirectoryEntries(const std::string &directoryPath)
    {
        std::vector<DirectoryEntry> paths;
        std::vector<std::string> filePaths = GetFilePathsInDirectory(directoryPath);
        std::vector<std::string> folderPaths = GetFolderPathsInDirectory(directoryPath);

        for (std::string fP : folderPaths)
        {
            DirectoryEntry p;
            p.Filename = fP;
            p.IsFolder = true;

            paths.emplace_back(p);
        }

        for (std::string fP : filePaths)
        {
            DirectoryEntry p;
            p.Filename = fP;
            p.IsFolder = false;

            paths.emplace_back(p);
        }

        return paths;
    }
}
#endif
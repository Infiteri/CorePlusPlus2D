#pragma once

#ifdef __WIN32
#define CE_WIN32
#elif defined(__linux__)
#define CE_LINUX
#elif defined(__APPLE__)
#define CE_MACOS
#else
#define CE_UNKNOWN_PLATFORM
#endif

//? Whether or not its in debug mode.
#ifdef _DEBUG
#define CE_DEBUG_MODE 1
#else
#define CE_DEBUG_MODE 0
#endif

// TODO: Version
// The current version
#define CE_VERSION "0.0.0.1"

// Define CE_API macros

#ifdef CE_WIN32
// The dll export
#define CE_API __declspec(dllexport)
#else
// The dll import
#define CE_API __declspec(dllimport)
#endif

//? Common types

typedef unsigned char CeU8;
typedef unsigned short CeU16;
typedef unsigned int CeU32;
typedef unsigned long long CeU64;

typedef signed char CeI8;
typedef signed short CeI16;
typedef signed int CeI32;
typedef signed long long CeI64;

#define CE_FUNCTION_SIGNATURE

#ifdef _MSVC_VER_
#undef CE_FUNCTION_SIGNATURE
#define CE_FUNCTION_SIGNATURE __FUNCSIG__
#else
#undef CE_FUNCTION_SIGNATURE
#define CE_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif

#define CE_EXPORT_ACTOR_CLASS(name) \
    extern "C" __declspec(dllexport) Core::ActorScript *name##Create() { return new name(); }

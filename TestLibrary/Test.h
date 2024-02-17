#pragma once

#include "Core.h"

extern "C" __declspec(dllexport) void TestStuff()
{
    CE_INFO("Hello from within library.");
};
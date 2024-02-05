#pragma once

#include "Core.h"
#include <string>

namespace Core
{
    class Test
    {
    public:
        std::string name;

        Test(const std::string &_name = "DEFAULT_TEST_NAME");
        ~Test();

        virtual bool Run();
    };
}
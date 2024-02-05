
#include "Test.h"

namespace Core
{
    Test::Test(const std::string &_name)
    {
        name = _name;
    }

    Test::~Test()
    {
    }

    bool Test::Run()
    {
        return true;
    }
}
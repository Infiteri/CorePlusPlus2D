#include "Input.h"
#include <unordered_map>

namespace Core
{
    struct State
    {
        std::unordered_map<Input::Keys, bool> keys;
    };

    static State state;

    void Input::Init()
    {
    }

    void Input::Shutdown()
    {
    }

    bool Input::GetKey(Keys key)
    {
        return state.keys[key] == true;
    }

    void INPUT_INTERNAL_UpdateKey(Input::Keys key, bool pressed)
    {
        state.keys[key] = pressed;
    }
}
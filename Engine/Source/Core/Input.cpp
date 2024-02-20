#include "Input.h"
#include "Math/Math.h"
#include "Core/Logger.h"
#include <unordered_map>

namespace Core
{
    struct State
    {
        std::unordered_map<Input::Keys, bool> keys;
        std::unordered_map<Input::Buttons, bool> buttons;

        Vector2 position;
        Vector2 last;
        Vector2 delta;

        float lastScroll;
        float deltaScroll;
        bool negativeDelta = false;
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

    bool Input::GetButton(Buttons button)
    {
        return state.buttons[button] == true;
    }

    int Input::GetMouseX()
    {
        return state.position.x;
    }

    int Input::GetMouseY()
    {
        return state.position.y;
    }

    int Input::GetMouseLastX()
    {
        return state.last.x;
    }

    int Input::GetMouseLastY()
    {
        return state.last.y;
    }

    int Input::GetMouseDeltaX()
    {
        return state.delta.x;
    }

    int Input::GetMouseDeltaY()
    {
        return state.delta.y;
    }

    Vector2 Input::GetMousePosition()
    {
        return {state.position.x, state.position.y};
    }

    Vector2 Input::GetMouseDelta()
    {
        return {state.delta.x, state.delta.y};
    }

    float Input::GetMouseWheelDelta()
    {
        return state.deltaScroll * state.negativeDelta;
    }

    void INPUT_INTERNAL_UpdateKey(Input::Keys key, bool pressed)
    {
        state.keys[key] = pressed;
    }

    void INPUT_INTERNAL_UpdateButton(Input::Buttons button, bool pressed)
    {
        state.buttons[button] = pressed;
    }

    void INPUT_INTERNAL_UpdateMouse(float x, float y)
    {

        state.delta.Set(x - state.last.x, y - state.last.y);
        state.position.Set(x, y);
        state.last.Set(x, y);
    }

    void INPUT_INTERNAL_UpdateScroll(double x, double y)
    {
        state.deltaScroll = 0;

        if (y == 0)
        {
            state.lastScroll = 0;
            return;
        }

        if (y < 0)
        {
            state.deltaScroll = y - Math::Positive(state.lastScroll);
            state.lastScroll = Math::Positive(y);
            state.negativeDelta = -1;
        }
        else
        {
            state.deltaScroll = y - Math::Positive(state.lastScroll);
            state.lastScroll = Math::Positive(y);
            state.negativeDelta = 1;
        }
    }
}
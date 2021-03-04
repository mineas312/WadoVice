#include "MouseHandler.hpp"
#include <Windows.h>

MouseHandler::MouseHandler()
{}

void MouseHandler::move_mouse(int x, int y)
{
    SetCursorPos(x, y);
}

void MouseHandler::click_mouse(MOUSE_CLICK mc)
{
    INPUT input;
    input.type = INPUT_MOUSE;

    POINT cursor_pos;
    GetCursorPos(&cursor_pos);

    switch(mc)
    {
        case MOUSE_CLICK::LEFT:
        {
            input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP);
            break;
        }
        case MOUSE_CLICK::RIGHT:
        {
            input.mi.dwFlags = (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP);
            break;
        }
    }

    SendInput(1, &input, sizeof(INPUT));
}
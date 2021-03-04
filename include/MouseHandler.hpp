#pragma once

enum class MOUSE_CLICK
{
    LEFT = 0,
    RIGHT
};

class MouseHandler
{
public:
    MouseHandler();

    // Przesuwa mysz w dane miejsce
    static void move_mouse(int x, int y);

    // Klika myszą
    static void click_mouse(MOUSE_CLICK mc);
};
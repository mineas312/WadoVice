#pragma once
#include <windows.h>
#include <string>

#include <Drawing/DirectX.hpp>

class BorderlessTransparentWindow
{
    public:
        BorderlessTransparentWindow(HINSTANCE hInstance, std::string title, int speed = 3);

    private:
        void prepare_window(std::string title, int speed);

    private:
        HINSTANCE hInstance;
        static LRESULT CALLBACK BorderlessTransparentWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        DirectX dx;
};

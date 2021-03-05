#pragma once
#include <Windows.h>
#include <string>
#include <thread>

#include <Drawing/DirectX.hpp>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class BorderlessTransparentWindow
{
    public:
        BorderlessTransparentWindow();

        // Okna muszą mieć unikatowe nazwy
        void create_window(HINSTANCE hInstance, std::string resource, std::string title, int speed = 3);

    private:
        void prepare_window(HINSTANCE hInstance, std::string resource, std::string title, int speed);

    private:
        HINSTANCE hInstance;
        DirectX* dx;
        std::thread window_thread;
};

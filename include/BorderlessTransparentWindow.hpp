#pragma once
#include <Windows.h>
#include <string>
#include <thread>
#include <vector>
#include <Drawing/Animation.hpp>
#include <Drawing/DirectX.hpp>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class BorderlessTransparentWindow
{
  public:
    BorderlessTransparentWindow();

    // Okna muszą mieć unikatowe nazwy
    void create_window(HINSTANCE hInst, std::vector<Animation *> animations, std::string title, int width, int height);
    DirectX *dx;

  private:
    void prepare_window(HINSTANCE hInst, std::vector<Animation *> animations, std::string title, int width, int height);

  private:
    HINSTANCE hInstance;
    std::thread window_thread;
};

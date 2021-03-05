#pragma once
#include <windows.h>
class Kremuwka
{
  public:
    Kremuwka(HINSTANCE hInstance);
    void Kremuwkuj(int speed = 3);

  private:
    HINSTANCE hInstance;
    static LRESULT CALLBACK Kremuwka::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

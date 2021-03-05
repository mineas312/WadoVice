#include <Windows.h>
#include <string>
#include <thread>

#include "DirectX.h"
DirectX DX9;

#include "Draw.h"
#include "Image.h"

#define SCREENWIDTH ::GetSystemMetrics(SM_CXSCREEN)
#define SCREENHEIGHT ::GetSystemMetrics(SM_CYSCREEN)

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
            break;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Kremuwkuj(HINSTANCE hInstance)
{
    WNDCLASSEXA wc;
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_NOCLOSE;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hIconSm = 0;
    wc.hCursor = 0;
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

    std::string sName = "test";

    wc.lpszMenuName = sName.c_str();
    wc.lpszClassName = sName.c_str();

    if (!RegisterClassExA(&wc))
    {
        ::UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return;
    }

    HWND hWnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_LAYERED, sName.c_str(), sName.c_str(), WS_POPUP, 1, 1, SCREENWIDTH, SCREENHEIGHT, 0, 0, 0, 0);
    SetLayeredWindowAttributes(hWnd, 0, 0, LWA_ALPHA);
    SetLayeredWindowAttributes(hWnd, 0, 0, LWA_COLORKEY);

    if (!DX9.Init(hWnd))
    {
        DX9.Cleanup();
        ::UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return;
    }

    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hWnd);

    Image *kremuwka = new Image(images::test, sizeof(images::test));

    MSG Msg;
    ZeroMemory(&Msg, sizeof(Msg));
    while (Msg.message != WM_QUIT)
    {
        if (PeekMessage(&Msg, hWnd, 0, 0, PM_REMOVE))
        {
            ::DispatchMessage(&Msg);
            ::TranslateMessage(&Msg);
            continue;
        }

        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            Draw draw;
            draw.Line(0, 0, 500, 500, RGBA(255, 0, 0), 3);
            kremuwka->Draw(100, 100);
            draw.String("asdasda123", 500, 500, centered, RGBA(0, 255, 0), DX9.fontTahoma, true);

            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            g_pd3dDevice->Reset(&g_d3dpp);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    DX9.Cleanup();
    ::DestroyWindow(hWnd);
    ::UnregisterClassA(wc.lpszClassName, wc.hInstance);
}

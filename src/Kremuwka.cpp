#include <Windows.h>
#include <string>
#include <thread>

#include <Drawing/DirectX.hpp>
DirectX DX9;

#include <Drawing/Draw.hpp>
#include <Drawing/Image.hpp>
#include <ResourceUtil.hpp>
#include <Kremuwka.hpp>

#define SCREENWIDTH ::GetSystemMetrics(SM_CXSCREEN)
#define SCREENHEIGHT ::GetSystemMetrics(SM_CYSCREEN)

Kremuwka::Kremuwka(HINSTANCE hInst)
{
    hInstance = hInst;
}

LRESULT CALLBACK Kremuwka::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

void Kremuwka::Kremuwkuj(int speed)
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

    std::string sName = "KREMUWA";

    wc.lpszMenuName = sName.c_str();
    wc.lpszClassName = sName.c_str();

    if (!RegisterClassExA(&wc))
    {
        ::UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return;
    }

    HWND hWnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW, sName.c_str(), sName.c_str(), WS_POPUP, 1, 1, SCREENWIDTH, SCREENHEIGHT, 0, 0, 0, 0);
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

    ResourceMem img = ResourceUtil::GetResourceMemory("KREMUWA");
    Image *kremuwka = new Image((const BYTE *)img.start, (int)img.size);
    int x = 0;
    int y = 0;
    int x_dir = 0;
    int y_dir = 0;

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
            /* Draw draw;
             * draw.Line(0, 0, 500, 500, RGBA(255, 0, 0), 3);
             * draw.String("asdasda123", 500, 500, centered, RGBA(0, 255, 0), DX9.fontTahoma, true); */
            if (y >= SCREENHEIGHT - (int)(kremuwka->info.Height))
                y_dir = 1;
            if (y <= 0)
                y_dir = 0;
            if (x >= SCREENWIDTH - (int)(kremuwka->info.Width))
                x_dir = 1;
            if (x <= 0)
                x_dir = 0;

            x += x_dir ? -speed : speed;
            y += y_dir ? -speed : speed;
            kremuwka->Draw(x, y);
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

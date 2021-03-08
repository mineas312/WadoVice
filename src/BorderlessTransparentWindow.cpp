#include <Drawing/Animation.hpp>
#include <Drawing/Draw.hpp>
#include <Drawing/Image.hpp>
#include <ResourceUtil.hpp>
#include <BorderlessTransparentWindow.hpp>
#include <iostream>
#include <vector>

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

BorderlessTransparentWindow::BorderlessTransparentWindow()
{
    dx = new DirectX();
}

void BorderlessTransparentWindow::create_window(HINSTANCE hInst, std::vector<Animation *> animations, std::string title, int width, int height)
{
    hInstance = hInst;
    window_thread = std::thread(&BorderlessTransparentWindow::prepare_window, this, hInst, animations, title, width, height);
}

void BorderlessTransparentWindow::prepare_window(HINSTANCE hInstance, std::vector<Animation *> animations, std::string title, int width, int height)
{
    // Create window class
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

    wc.lpszMenuName = title.c_str();
    wc.lpszClassName = title.c_str();

    // Register class
    if (!RegisterClassExA(&wc))
    {
        std::cout << GetLastError() << std::endl;
        UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return;
    }

    // Create window
    HWND hWnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW, title.c_str(), title.c_str(), WS_POPUP, 1, 1, width, height, 0, 0, 0, 0);
    std::cout << GetLastError() << std::endl;
    SetLayeredWindowAttributes(hWnd, 0, 0, LWA_ALPHA);
    SetLayeredWindowAttributes(hWnd, 0, 0, LWA_COLORKEY);

    // Hook d3d to the window
    if (!dx->Init(hWnd))
    {
        dx->Cleanup();
        UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return;
    }

    // Update and show window
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    for (Animation *a : animations)
    {
        a->DXInitialized();
    }

    MSG Msg;
    ZeroMemory(&Msg, sizeof(Msg));

    while (Msg.message != WM_QUIT)
    {
        if (PeekMessage(&Msg, hWnd, 0, 0, PM_REMOVE))
        {
            DispatchMessage(&Msg);
            TranslateMessage(&Msg);
            continue;
        }
        dx->pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        dx->pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        dx->pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        dx->pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (dx->pd3dDevice->BeginScene() >= 0)
        {
            // Draw draw;
            // draw.Line(0, 0, 500, 500, RGBA(255, 0, 0), 3);
            // draw.String("asdasda123", 500, 500, centered, RGBA(0, 255, 0), DX9.fontTahoma, true);
            for (Animation *a : animations)
            {
                a->DrawFrame();
            }
            dx->pd3dDevice->EndScene();
        }
        HRESULT result = dx->pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && dx->pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            dx->pd3dDevice->Reset(&dx->d3dpp);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    dx->Cleanup();
    DestroyWindow(hWnd);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);
}

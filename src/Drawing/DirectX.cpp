#include <Drawing/DirectX.hpp>

bool DirectX::Init(HWND hWnd)
{
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice) < 0)
        return false;

    if (FAILED(D3DXCreateLine(pd3dDevice, &Line)))
    {
        if (pd3dDevice)
        {
            pd3dDevice->Release();
            pd3dDevice = NULL;
        }
        if (pD3D)
        {
            pD3D->Release();
            pD3D = NULL;
        }
        return false;
    }

    Line->SetWidth(1.0f);
    Line->SetPattern(0xFFFFFFFF);
    Line->SetAntialias(false);

    D3DXCreateFontA(pd3dDevice, 16, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &fontTahoma);

    return true;
}

void DirectX::Cleanup()
{
    if (pd3dDevice)
    {
        pd3dDevice->Release();
        pd3dDevice = NULL;
    }
    if (pD3D)
    {
        pD3D->Release();
        pD3D = NULL;
    }
    if (Line != NULL)
    {
        Line->Release();
    }
}

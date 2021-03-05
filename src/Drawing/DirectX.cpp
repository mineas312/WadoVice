#include <Drawing/DirectX.hpp>

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
D3DPRESENT_PARAMETERS g_d3dpp = {};
ID3DXLine *g_Line = NULL;

bool DirectX::Init(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    if (FAILED(D3DXCreateLine(g_pd3dDevice, &g_Line)))
    {
        if (g_pd3dDevice)
        {
            g_pd3dDevice->Release();
            g_pd3dDevice = NULL;
        }
        if (g_pD3D)
        {
            g_pD3D->Release();
            g_pD3D = NULL;
        }
        return false;
    }

    g_Line->SetWidth(1.0f);
    g_Line->SetPattern(0xFFFFFFFF);
    g_Line->SetAntialias(false);

    D3DXCreateFontA(g_pd3dDevice, 16, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &fontTahoma);

    return true;
}

void DirectX::Cleanup()
{
    if (g_pd3dDevice)
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = NULL;
    }
    if (g_pD3D)
    {
        g_pD3D->Release();
        g_pD3D = NULL;
    }
    if (g_Line != NULL)
    {
        g_Line->Release();
    }
}

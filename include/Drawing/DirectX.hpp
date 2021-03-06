#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class DirectX
{
  public:
    bool Init(HWND hWnd);
    void Cleanup();

  public:
    ID3DXFont *fontTahoma;
    LPDIRECT3D9 pD3D;
    LPDIRECT3DDEVICE9 pd3dDevice;
    D3DPRESENT_PARAMETERS d3dpp;
    ID3DXLine *Line;
};

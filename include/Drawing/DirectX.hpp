#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LPDIRECT3D9 g_pD3D;
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern D3DPRESENT_PARAMETERS g_d3dpp;
extern ID3DXLine *g_Line;

class DirectX
{
  private:
  public:
    ID3DXFont *fontTahoma;

    bool Init(HWND hWnd);
    void Cleanup();
};

extern DirectX DX9;

#pragma once
#include "DirectX.hpp"

class Image
{
  public:
    LPDIRECT3DTEXTURE9 texture = NULL;
    LPD3DXSPRITE sprite = NULL;
    D3DXIMAGE_INFO info;
    D3DXVECTOR3 pos;
    Image();
    ~Image()
    {
        if (texture)
        {
            texture->Release();
            texture = NULL;
        }
        if (sprite)
        {
            sprite->Release();
            sprite = NULL;
        }
    }

    Image(const BYTE *image, int size);

    void Draw(int x, int y, int z = 0);
};

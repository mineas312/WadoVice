#include "Image.h"

Image::Image(const BYTE *image, int size)
{
    if (image)
    {
        if (!texture)
            D3DXCreateTextureFromFileInMemory(g_pd3dDevice, image, size, &texture);

        /*	D3DSURFACE_DESC imgDesc;
			texture->GetLevelDesc(0, &imgDesc);
			imgDesc.Height = h;
			imgDesc.Width = w;*/

        if (!sprite)
            D3DXCreateSprite(g_pd3dDevice, &sprite);
    }
}
void Image::Draw(int x, int y, int z)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    sprite->Draw(texture, NULL, NULL, &pos, 0xFFFFFFFF);
    sprite->End();
}
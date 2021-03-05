#include <Drawing/Image.hpp>

Image::Image(const BYTE *image, int size, DirectX dx)
{
    if (image)
    {
        if (!texture)
        {
            D3DXCreateTextureFromFileInMemory(dx.pd3dDevice, image, size, &texture);
            D3DXGetImageInfoFromFileInMemory(image, size, &info);
        }

        /*	D3DSURFACE_DESC imgDesc;
			texture->GetLevelDesc(0, &imgDesc);
			imgDesc.Height = h;
			imgDesc.Width = w;*/

        if (!sprite)
            D3DXCreateSprite(dx.pd3dDevice, &sprite);
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

#include <Drawing/Anims/Kremuwka.hpp>
#include <ResourceUtil.hpp>

Kremuwka::Kremuwka(DirectX *p_dx, int p_screen_width, int p_screen_height, int p_start_x, int p_start_y, int p_speed) : Animation(p_dx)
{
    dx = p_dx;
    screen_width = p_screen_width;
    screen_height = p_screen_height;
    x = p_start_x;
    y = p_start_y;
    x_dir = 0;
    y_dir = 0;
    speed = p_speed;
}
void Kremuwka::DXInitialized()
{
    ResourceMem res = ResourceUtil::GetResourceMemory("KREMUWA");
    img = new Image((const BYTE *)res.start, (int)res.size, *dx);
}
void Kremuwka::DrawFrame()
{
    if (y >= screen_height - (int)(img->info.Height))
        y_dir = 1;
    if (y <= 0)
        y_dir = 0;
    if (x >= screen_width - (int)(img->info.Width))
        x_dir = 1;
    if (x <= 0)
        x_dir = 0;
    x += x_dir ? -speed : speed;
    y += y_dir ? -speed : speed;
    img->Draw(x, y);
}

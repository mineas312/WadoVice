#pragma once

#include "../DirectX.hpp"
#include "../Image.hpp"
#include "../Animation.hpp"

class Kremuwka : public Animation
{
  public:
    Kremuwka(DirectX *directx, int screen_width, int screen_height, int start_x, int start_y, int speed = 10);
    void DrawFrame();
    void DXInitialized();

  private:
    DirectX *dx;
    Image *img;
    int screen_width;
    int screen_height;
    int x;
    int y;
    int x_dir;
    int y_dir;
    int speed;
};

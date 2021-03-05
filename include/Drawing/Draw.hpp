#pragma once

#include <string>
#include "RGBA.hpp"
#include "Image.hpp"

enum text_alignment : int
{
    lefted = 0,
    centered = 1,
    righted = 2
};

class Draw
{
  public:
    static void Line(int x, int y, int x2, int y2, RGBA rgb, DirectX dx, float thickness = 1.f);
    static void String(std::string text, int x, int y, int orientation, RGBA color, ID3DXFont *font, bool bordered = true, RGBA bcolor = RGBA(1, 0, 0));
};

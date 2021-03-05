#pragma once

#include <string>

#include "RGBA.h"
#include "Image.h"

enum text_alignment : int
{
	lefted = 0,
	centered = 1,
	righted = 2
};

class Draw
{
private:

public:

	void Line(int x, int y, int x2, int y2, RGBA rgb, float thickness = 1.f);
	void String(std::string text, int x, int y, int orientation, RGBA color, ID3DXFont* font, bool bordered = true, RGBA bcolor = RGBA(1, 0, 0));
};

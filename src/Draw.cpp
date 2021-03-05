#include "Draw.h"
#include "DirectX.h"

void Draw::Line(int x, int y, int x2, int y2, RGBA rgb, float thickness)
{
	g_Line->SetWidth(thickness);
	D3DXVECTOR2 points[2];
	points[0].x = x;
	points[1].x = x2;
	points[0].y = y;
	points[1].y = y2;
	g_Line->Draw(points, 2, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B));
}

void Draw::String(std::string text, int x, int y, int orientation, RGBA color, ID3DXFont* font, bool bordered, RGBA bcolor)
{
	RECT rect;

	switch (orientation)
	{
	case lefted:
		if (bordered)
		{
			SetRect(&rect, x - 1, y, x - 1, y);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x + 1, y, x + 1, y);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x, y - 1, x, y - 1);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x, y + 1, x, y + 1);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
		}
		SetRect(&rect, x, y, x, y);
		font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		break;
	case centered:
		if (bordered)
		{
			SetRect(&rect, x - 1, y, x - 1, y);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x + 1, y, x + 1, y);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x, y - 1, x, y - 1);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x, y + 1, x, y + 1);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
		}
		SetRect(&rect, x, y, x, y);
		font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		break;
	case righted:
		if (bordered)
		{
			SetRect(&rect, x - 1, y, x - 1, y);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x + 1, y, x + 1, y);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x, y - 1, x, y - 1);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
			SetRect(&rect, x, y + 1, x, y + 1);
			font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(bcolor.A, bcolor.R, bcolor.G, bcolor.B));
		}
		SetRect(&rect, x, y, x, y);
		font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		break;
	}
}
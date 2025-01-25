// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#include "Renderer.h"
#include "Utilities.h"

void RenderBackground()
{
	u32* CurrentPixel = (u32*)RenderState.BufferMemory;

	for (int y = 0; y < RenderState.BufferHeight; y++)
	{
		for (int x = 0; x < RenderState.BufferWidth; x++)
		{
			*CurrentPixel++ = x * y;
		}
	}
};

void ClearScreen(u32 Color)
{
	u32* CurrentPixel = (u32*)RenderState.BufferMemory;

	for (int y = 0; y < RenderState.BufferHeight; y++)
	{
		for (int x = 0; x < RenderState.BufferWidth; x++)
		{
			*CurrentPixel++ = Color;
		}
	}
}

void DrawRectangle_InPixels(int X0, int Y0, int X1, int Y1, u32 Color)
{
	X0 = ClampInt(0, X0, RenderState.BufferWidth);
	X1 = ClampInt(0, X1, RenderState.BufferWidth);
	Y0 = ClampInt(0, Y0, RenderState.BufferHeight);
	Y1 = ClampInt(0, Y1, RenderState.BufferHeight);

	for (int y = Y0; y < Y1; y++)
	{
		u32* CurrentPixel = (u32*)RenderState.BufferMemory + X0 + y * RenderState.BufferWidth;

		for (int x = X0; x < X1; x++)
		{
			*CurrentPixel++ = Color;
		}
	}
}

void DrawRectangle(float X, float Y, float HalfSize_X, float HalfSize_Y, u32 Color)
{
	X *= RenderState.BufferHeight * RenderScale;
	Y *= RenderState.BufferHeight * RenderScale;
	HalfSize_X *= RenderState.BufferHeight * RenderScale;
	HalfSize_Y *= RenderState.BufferHeight * RenderScale;

	X += RenderState.BufferWidth / 2.f;
	Y += RenderState.BufferHeight / 2.f;

	// Change to Pixels
	int X0 = X - HalfSize_X;
	int X1 = X + HalfSize_X;
	int Y0 = Y - HalfSize_Y;
	int Y1 = Y + HalfSize_Y;

	DrawRectangle_InPixels(X0, Y0, X1, Y1, Color);
}

void DrawNumber(int number, int x, int y, float size, u32 color)
{
	float HalfSize = size * .5f;
	bool DrawZero = false;

	while (number != 0 || !DrawZero)
	{
		DrawZero = true;
		int Digit = number % 10;
		number = number / 10;

		switch (Digit)
		{
		case 0:
		{
			DrawRectangle(x - size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x, y + size * 2.f, HalfSize, HalfSize, color);
			DrawRectangle(x, y - size * 2.f, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 1:
		{
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			x -= size * 4.f;
		}break;

		case 2:
		{
			DrawRectangle(x, y + size * 2.f, 1.5f * size, HalfSize, color);
			DrawRectangle(x, y, 1.5f * size, HalfSize, color);
			DrawRectangle(x, y - size * 2.f, 1.5f * size, HalfSize, color);
			DrawRectangle(x + size, y + size, HalfSize, HalfSize, color);
			DrawRectangle(x - size, y - size, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 3:
		{
			DrawRectangle(x - HalfSize, y + size * 2.f, size, HalfSize, color);
			DrawRectangle(x - HalfSize, y, size, HalfSize, color);
			DrawRectangle(x - HalfSize, y - size * 2.f, size, HalfSize, color);
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			x -= size * 4.f;
		}break;

		case 4:
		{
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x - size, y + size, HalfSize, 1.5f * size, color);
			DrawRectangle(x, y, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 5:
		{
			DrawRectangle(x, y + size * 2.f, 1.5f * size, HalfSize, color);
			DrawRectangle(x, y, 1.5f * size, HalfSize, color);
			DrawRectangle(x, y - size * 2.f, 1.5f * size, HalfSize, color);
			DrawRectangle(x - size, y + size, HalfSize, HalfSize, color);
			DrawRectangle(x + size, y - size, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 6:
		{
			DrawRectangle(x + HalfSize, y + size * 2.f, size, HalfSize, color);
			DrawRectangle(x + HalfSize, y, size, HalfSize, color);
			DrawRectangle(x + HalfSize, y - size * 2.f, size, HalfSize, color);
			DrawRectangle(x - size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x + size, y - size, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 7:
		{
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x - HalfSize, y + size * 2.f, size, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 8:
		{
			DrawRectangle(x - size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x, y + size * 2.f, HalfSize, HalfSize, color);
			DrawRectangle(x, y - size * 2.f, HalfSize, HalfSize, color);
			DrawRectangle(x, y, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;

		case 9:
		{
			DrawRectangle(x - HalfSize, y + size * 2.f, size, HalfSize, color);
			DrawRectangle(x - HalfSize, y, size, HalfSize, color);
			DrawRectangle(x - HalfSize, y - size * 2.f, size, HalfSize, color);
			DrawRectangle(x + size, y, HalfSize, 2.5f * size, color);
			DrawRectangle(x - size, y + size, HalfSize, HalfSize, color);
			x -= size * 4.f;
		}break;
		}
	}
}

void Draw_Text(const char* text, float x, float y, float size, u32 color)
{
	float HalfSize = size * .5f;
	float Original_Y = y;

	while (*text) 
	{
		if (*text != 32) 
		{
			const char** Letter;
			if (*text == 47) Letter = letters[27];
			else if (*text == 46) Letter = letters[26];
			else Letter = letters[*text - 'A'];
			float Original_X = x;

			for (int i = 0; i < 7; i++) 
			{
				const char* Row = Letter[i];
				while (*Row) 
				{
					if (*Row == '0') 
					{
						DrawRectangle(x, y, HalfSize, HalfSize, color);
					}
					x += size;
					Row++;
				}
				y -= size;
				x = Original_X;
			}
		}
		text++;
		x += size * 6.f;
		y = Original_Y;
	}
}

void Drawborder(float AreaX, float AreaY, u32 color)
{
	AreaX *= RenderState.BufferHeight * RenderScale;
	AreaY *= RenderState.BufferHeight * RenderScale;

	int x0 = (int)((float)RenderState.BufferWidth * .5f - AreaX);
	int x1 = (int)((float)RenderState.BufferWidth * .5f + AreaX);
	int y0 = (int)((float)RenderState.BufferHeight * .5f - AreaY);
	int y1 = (int)((float)RenderState.BufferHeight * .5f + AreaY);

	DrawRectangle_InPixels(0, 0, RenderState.BufferWidth, y0, color);
	DrawRectangle_InPixels(0, y1, x1, RenderState.BufferHeight, color);
	DrawRectangle_InPixels(0, y0, x0, y1, color);
	DrawRectangle_InPixels(x1, y0, RenderState.BufferWidth, RenderState.BufferHeight, color);
}

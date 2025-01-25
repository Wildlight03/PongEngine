// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#pragma once

#include "PongEngineTypes.h"
#include "main.h"


static float RenderScale = 0.01f;

void RenderBackground();
void ClearScreen(u32 Color);
void DrawRectangle_InPixels(int X0, int Y0, int X1, int Y1, u32 Color);
void DrawRectangle(float X, float Y, float HalfSize_X, float HalfSize_Y, u32 Color);
void DrawNumber(int number, int PosX, int PosY, float size, u32 color);
void Draw_Text(const char* text, float x, float y, float size, u32 color);
void Drawborder(float AreaX, float AreaY, u32 color);


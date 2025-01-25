// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#pragma once
// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#include <Windows.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define Is_Down(b) Input->Buttons[b].IsDown
#define Pressed(b) (Input->Buttons[b].IsDown && Input->Buttons[b].IsDirty)
#define Released(b) (!Input->Buttons[b].IsDown && Input->Buttons[b].IsDirty)

#define Process_Button(b, vk)\
case vk: {\
Input.Buttons[b].IsDirty = IsDown != Input.Buttons[b].IsDown;\
Input.Buttons[b].IsDown = IsDown;\
}break;



struct FVector2D
{
	float X = 0.f;
	float Y = 0.f;

	FVector2D(float InX = 0.f, float InY = 0.f) : X(InX), Y(InY) {}
};


struct FRenderState
{
	int BufferHeight, BufferWidth;
	void* BufferMemory = nullptr;
	BITMAPINFO BufferBitmapInfo;
};

struct FButtonState 
{
	bool IsDown;
	bool IsDirty;
};

enum EButtonStates
{
	ButtonUp,
	ButtonDown,
	ButtonLeft,
	ButtonRight,
	Button_W,
	Button_S,
	Button_Enter,
	ButtonCount // Should be Last Item
};

struct FButtonInput 
{
	FButtonState Buttons[ButtonCount];
};
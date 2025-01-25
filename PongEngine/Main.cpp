// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#include "Main.h"
#include "Pong.h"


FRenderState RenderState;

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (uMsg)
	{
		case WM_CLOSE : 
		case WM_DESTROY: 
		{ 
			bRunning = false; 
		} break;

		case WM_SIZE: 
		{
			RECT Rect;
			GetClientRect(hwnd, &Rect);
			RenderState.BufferWidth = Rect.right - Rect.left;
			RenderState.BufferHeight = Rect.bottom - Rect.top;
			int BufferSize = RenderState.BufferWidth * RenderState.BufferHeight * sizeof(u32);

			if (RenderState.BufferMemory)
				VirtualFree(RenderState.BufferMemory, 0, MEM_RELEASE);

			RenderState.BufferMemory = VirtualAlloc(0, BufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			RenderState.BufferBitmapInfo.bmiHeader.biSize = sizeof(RenderState.BufferBitmapInfo.bmiHeader);
			RenderState.BufferBitmapInfo.bmiHeader.biWidth = RenderState.BufferWidth;
			RenderState.BufferBitmapInfo.bmiHeader.biHeight = RenderState.BufferHeight;
			RenderState.BufferBitmapInfo.bmiHeader.biPlanes = 1;
			RenderState.BufferBitmapInfo.bmiHeader.biBitCount = 32;
			RenderState.BufferBitmapInfo.bmiHeader.biCompression = BI_RGB;

		} break;

		default: { Result = DefWindowProc(hwnd, uMsg, wParam, lParam); }
	}

	return Result;
}


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpszClassName = "Game Window Class";
	WindowClass.lpfnWndProc = WindowCallback;

	RegisterClass(&WindowClass);

	HWND Window = CreateWindow(WindowClass.lpszClassName, "Pong Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(Window);

	FButtonInput Input = {};
	
	float Delta_Time = 0.016666f;
	LARGE_INTEGER Frame_Begin_Time;
	QueryPerformanceCounter(&Frame_Begin_Time);

	float PerformanceFrequency;
	{
		LARGE_INTEGER Perforamnce;
		QueryPerformanceFrequency(&Perforamnce);
		PerformanceFrequency = (float)Perforamnce.QuadPart;
	}
	
	while (bRunning)
	{
		MSG Message;

		for (int i = 0; i < ButtonCount; i++)
		{
			Input.Buttons[i].IsDirty = false;
		}

		while (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			switch (Message.message)
			{
				case WM_KEYUP:
				case WM_KEYDOWN: 
				{
					u32 vk_code = (u32)Message.wParam;
					bool IsDown = ((Message.lParam & (1 << 31)) == 0);

					switch (vk_code)
					{
						Process_Button(ButtonUp, VK_UP);
						Process_Button(ButtonDown, VK_DOWN);
						Process_Button(ButtonLeft, VK_LEFT);
						Process_Button(ButtonRight, VK_RIGHT);
						Process_Button(Button_Enter, VK_RETURN);
						Process_Button(Button_W, 'W');
						Process_Button(Button_S, 'S');
					}
				
				}break;

				default:
					TranslateMessage(&Message);
					DispatchMessage(&Message);
			}
		}

		SimulateGame(&Input, Delta_Time);
		
		StretchDIBits(hdc, 0, 0, RenderState.BufferWidth, RenderState.BufferHeight, 0, 0, RenderState.BufferWidth, RenderState.BufferHeight, RenderState.BufferMemory, &RenderState.BufferBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER Frame_End_Time;
		QueryPerformanceCounter(&Frame_End_Time);
		Delta_Time = (float)(Frame_End_Time.QuadPart - Frame_Begin_Time.QuadPart) / PerformanceFrequency;
		Frame_Begin_Time = Frame_End_Time;

	};
}
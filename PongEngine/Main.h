// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#pragma once
// Copyright (C) 2025 Samuel Freeman. All rights reserved.

#include <Windows.h>
#include "PongEngineTypes.h"


static bool bRunning = true;
extern FRenderState RenderState;

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

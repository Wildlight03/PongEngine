// Copyright (C) 2025 Samuel Freeman. All rights reserved.


#pragma once

#include "PongEngineTypes.h"
#include <iostream>
#include <vector>


struct FPaddleInfo 
{
	float PaddlePosition = 0.f;
	float PaddleVelocity = 0.f;
};

struct FBallInfo
{
	FVector2D BallPosition = { 0.f, 0.f };
	FVector2D BallVelocity = { 100.f, 0.f };
};

enum GameMode
{
	GM_MENU,
	GM_GamePlay
};

static float PaddleHalfSize_X = 2.5;
static float PaddleHalfSize_Y = 12;
static int PaddleOffset = 75;
static float ArenaHalfSize_X = 85.f;
static float ArenaHalfSize_Y = 45.f;
static float BallHalfSize = 1;

static int RightPlayerScore, LeftPlayerScore;
static int ComputerReactionTime = 0;
static bool MenuButton = true;
static bool UseAi = true;

static FPaddleInfo RightPaddle;
static FPaddleInfo LeftPaddle;
static FBallInfo GameBall;

static GameMode CurrentGameMode = GM_MENU;

void SimulateGame(FButtonInput* Input, float Delta_Time);

void UpdatePaddlePosition(float& paddleAcceleration, FPaddleInfo& paddle, float delta_time, float speed);
void UpdateBallPosition(FBallInfo& gameball, float delta_time, float speed);
void CheckPaddleCollision(FBallInfo& gameball);
void CheckArenaCollision(FBallInfo& gameball);
void HandleInput(FButtonInput* Input, float& RightAccelleration, float& LefttAccelleratio);
void DisplayMenu(FButtonInput* Input);
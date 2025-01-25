// Copyright (C) 2025 Samuel Freeman. All rights reserved.


#include "Pong.h"
#include "Renderer.h"



void SimulateGame(FButtonInput* Input, float Delta_Time)
{
	ClearScreen(0xffffff);

	// Draw Arena
	//DrawRectangle(0, 0, ArenaHalfSize_X, ArenaHalfSize_Y, 0xffffff);

	Drawborder(ArenaHalfSize_X, ArenaHalfSize_Y, 0x000000);

	if (CurrentGameMode == GM_MENU)
	{
		DisplayMenu(Input);
		return;
	}
		

	float RightPaddleAcceleration = 0;
	float LeftPaddleAcceleration = 0;
	float PaddleSpeed = 40.f * Delta_Time;
	float BallSpeed = 15.f * Delta_Time;

	HandleInput(Input, RightPaddleAcceleration, LeftPaddleAcceleration);
	
	//Move Paddles
	UpdatePaddlePosition(RightPaddleAcceleration, RightPaddle, Delta_Time, PaddleSpeed);
	UpdatePaddlePosition(LeftPaddleAcceleration, LeftPaddle, Delta_Time, PaddleSpeed);

	UpdateBallPosition(GameBall, Delta_Time, BallSpeed);

	DrawNumber(RightPlayerScore, -10, 40, 1.f, 0x000000);
	DrawNumber(LeftPlayerScore, 10, 40, 1.f, 0x000000);

	// Draw Ball
	DrawRectangle(GameBall.BallPosition.X, GameBall.BallPosition.Y, BallHalfSize * 2, BallHalfSize * 2, 0x000000);

	// Draw Paddles
	DrawRectangle(PaddleOffset, RightPaddle.PaddlePosition, PaddleHalfSize_X, PaddleHalfSize_Y, 0x000000);
	DrawRectangle(-PaddleOffset, LeftPaddle.PaddlePosition, PaddleHalfSize_X, PaddleHalfSize_Y, 0x000000);
}

void HandleInput(FButtonInput* Input, float& RightAccelleration, float& LefttAccelleration)
{
	// Right Paddle Input
	if (Is_Down(ButtonUp))
		RightAccelleration += 2000;

	if (Is_Down(ButtonDown))
		RightAccelleration -= 2000;
	if (!UseAi)
	{
		// Left Paddle Input
		if (Is_Down(Button_W))
			LefttAccelleration += 2000;

		if (Is_Down(Button_S))
			LefttAccelleration -= 2000;
	}
	else
	{

		LefttAccelleration = (GameBall.BallPosition.Y - LeftPaddle.PaddlePosition) * (100 + ComputerReactionTime);
		if (LefttAccelleration > 2000) LefttAccelleration = 2000;
		if (LefttAccelleration < -2000) LefttAccelleration = -2000;
	}
}

void DisplayMenu(FButtonInput* Input)
{
	if (Pressed(ButtonRight) && MenuButton)
	{
		MenuButton = !MenuButton;
	}
	else if (Pressed(ButtonLeft) && !MenuButton)
	{
		MenuButton = !MenuButton;
	}

	Draw_Text("PONG", -60, 30, 2, 0x000000);

	Draw_Text("ENGINE", 5, 30, 2, 0x000000);

	if (Pressed(Button_Enter))
	{
		CurrentGameMode = GM_GamePlay;
		UseAi = MenuButton ? true : false;
	}

	if (MenuButton)
	{
		DrawRectangle(20, 0, 10, 10, 0xcccccc);
		DrawRectangle(-20, 0, 10, 10, 0x000000);

		Draw_Text("TWO", 12, 0, .3, 0x000000);
		Draw_Text("PLAYER", 18, 0, .3, 0x000000);
		Draw_Text("SINGLE", -29, 0, .25, 0xffffff);
		Draw_Text("PLAYER", -19, 0, .25, 0xffffff);
	}
	else
	{
		DrawRectangle(20, 0, 10, 10, 0x000000);
		DrawRectangle(-20, 0, 10, 10, 0xcccccc);

		Draw_Text("TWO", 12, 0, .3, 0xffffff);
		Draw_Text("PLAYER", 18, 0, .3, 0xffffff);
		Draw_Text("SINGLE", -29, 0, .25, 0x000000);
		Draw_Text("PLAYER", -19, 0, .25, 0x000000);
	}

	
}

void UpdatePaddlePosition(float& PaddleAcceleration, FPaddleInfo& Paddle, float Delta_Time, float speed)
{
	// Paddle Friction | Acceleration | Velocity
	PaddleAcceleration -= Paddle.PaddleVelocity * 10.f;
	Paddle.PaddlePosition = Paddle.PaddlePosition + Paddle.PaddleVelocity * Delta_Time + PaddleAcceleration * Delta_Time * Delta_Time * speed;
	Paddle.PaddleVelocity = Paddle.PaddleVelocity + PaddleAcceleration * Delta_Time;

	if (Paddle.PaddlePosition + PaddleHalfSize_Y > ArenaHalfSize_Y)
	{
		Paddle.PaddlePosition = ArenaHalfSize_Y - PaddleHalfSize_Y;
		Paddle.PaddleVelocity = 0;
	}
	else if (Paddle.PaddlePosition - PaddleHalfSize_Y < -ArenaHalfSize_Y)
	{
		Paddle.PaddlePosition = -ArenaHalfSize_Y + PaddleHalfSize_Y;
		Paddle.PaddleVelocity = 0;
	}
}

void UpdateBallPosition(FBallInfo& gameball, float delta_time, float speed)
{
	// Paddle Friction | Acceleration | Velocity
	
	gameball.BallPosition.X += gameball.BallVelocity.X * delta_time;
	gameball.BallPosition.Y += gameball.BallVelocity.Y * delta_time;

	CheckPaddleCollision(gameball);
	CheckArenaCollision(gameball);
}

void CheckPaddleCollision(FBallInfo& gameball)
{
	if (gameball.BallPosition.X + BallHalfSize > PaddleOffset - PaddleHalfSize_X &&
		gameball.BallPosition.X - BallHalfSize < PaddleOffset + PaddleHalfSize_X &&
		gameball.BallPosition.Y + BallHalfSize > RightPaddle.PaddlePosition - PaddleHalfSize_Y &&
		gameball.BallPosition.Y + BallHalfSize < RightPaddle.PaddlePosition + PaddleHalfSize_Y)
	{
		//Ball Hit Right Paddle
		gameball.BallPosition.X = PaddleOffset - PaddleHalfSize_X - BallHalfSize;
		gameball.BallVelocity.X *= -1;
		gameball.BallVelocity.Y = (gameball.BallPosition.Y - RightPaddle.PaddlePosition) + RightPaddle.PaddleVelocity * .75f;

	}
	else if (gameball.BallPosition.X + BallHalfSize > -PaddleOffset - PaddleHalfSize_X &&
		gameball.BallPosition.X - BallHalfSize < -PaddleOffset + PaddleHalfSize_X &&
		gameball.BallPosition.Y + BallHalfSize > LeftPaddle.PaddlePosition - PaddleHalfSize_Y &&
		gameball.BallPosition.Y + BallHalfSize < LeftPaddle.PaddlePosition + PaddleHalfSize_Y)
	{
		//Ball Hit Left Paddle
		gameball.BallPosition.X = -PaddleOffset + PaddleHalfSize_X + BallHalfSize;
		gameball.BallVelocity.X *= -1;
		gameball.BallVelocity.Y = (gameball.BallPosition.Y - LeftPaddle.PaddlePosition) + LeftPaddle.PaddleVelocity * .75f;
	}
}

void CheckArenaCollision(FBallInfo& gameball)
{
	// Check For Top / Bottom Collision
	if (gameball.BallPosition.Y + BallHalfSize > ArenaHalfSize_Y)
	{
		gameball.BallPosition.Y = ArenaHalfSize_Y - BallHalfSize;
		gameball.BallVelocity.Y *= -1;
	}
	else if (gameball.BallPosition.Y - BallHalfSize < -ArenaHalfSize_Y)
	{
		gameball.BallPosition.Y = -ArenaHalfSize_Y + BallHalfSize;
		gameball.BallVelocity.Y *= -1;
	}
	
	// Check For Side Collision
	if (gameball.BallPosition.X + BallHalfSize > ArenaHalfSize_X)
	{
		gameball.BallPosition.X = 0;
		gameball.BallPosition.Y = 0;
		gameball.BallVelocity.X = -100;
		gameball.BallVelocity.Y = 0;
		RightPlayerScore++;

		if (ComputerReactionTime > 0)
			ComputerReactionTime -= 50;
	}
	else if (gameball.BallPosition.X - BallHalfSize < -ArenaHalfSize_X)
	{
		gameball.BallPosition.X = 0;
		gameball.BallPosition.Y = 0;
		gameball.BallVelocity.X = 100;
		gameball.BallVelocity.Y = 0;
		LeftPlayerScore++;

		if (ComputerReactionTime < 2000)
			ComputerReactionTime += 50;
	}
}


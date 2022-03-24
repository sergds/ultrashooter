#include "AlsoStartGameState.h"

void AlsoStartGameState::Init()
{
	logger.Log("Initialized AlsoStartGameState!");
}

void AlsoStartGameState::Think()
{
	ClearBackground(BLACK);
	Vector2 pos{ 0,0 };
	DrawTextEx(GetFontDefault(), "Made by SergDS", CLITERAL(Vector2) { 280, 280 }, 40, 1, WHITE);
}

void AlsoStartGameState::Destroy()
{
}

AlsoStartGameState::AlsoStartGameState()
{
}

AlsoStartGameState::~AlsoStartGameState()
{
}

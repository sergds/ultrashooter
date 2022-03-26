#include "GameplayGameState.h"

void GameplayGameState::Init()
{
	bg = LoadTexture("data/sprites/battlefield.png");
}

void GameplayGameState::Think()
{
	DrawTexture(bg, 0, 0, WHITE);
	player.Think();
	testenemy.Think();

	DrawTextEx(DefaultFont, TextFormat("Score: %i", score), CLITERAL(Vector2){0, 25}, 25, 1, WHITE);
	DrawTextEx(DefaultFont, TextFormat("Lost: %i", prosrano), CLITERAL(Vector2){0, 55}, 25, 1, WHITE);
}

void GameplayGameState::Destroy()
{
}

GameplayGameState::GameplayGameState()
{
}

GameplayGameState::~GameplayGameState()
{
}

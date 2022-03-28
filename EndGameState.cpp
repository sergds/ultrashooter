#include "EndGameState.h"

void EndGameState::Init()
{
	music = LoadMusicStream("data/dailyagony.xm");
	PlayMusicStream(music);
}

void EndGameState::Think()
{
	ClearBackground(BLACK);
	DrawTextEx(DefaultFont, "GAME OVER", CLITERAL(Vector2){(float)GetRenderWidth() / 2 - 150, (float)GetRenderHeight() / 2 - 100}, 50, 1, WHITE);
	DrawTextEx(DefaultFont,TextFormat("Final Score: %i", globalscore), CLITERAL(Vector2) { (float)GetRenderWidth() / 2 - 200, (float)GetRenderHeight() / 2 }, 50, 1, WHITE);
	DrawTextEx(DefaultFont, TextFormat("Press [R] to return to the Main Menu"), CLITERAL(Vector2) { 0, (float)GetRenderHeight() - 50 }, 25, 1, WHITE);
	if (IsKeyPressed(KEY_R)) {
		SwitchGameState(new MainMenuGameState());
	}
}

void EndGameState::Destroy()
{
	StopMusicStream(music);
	UnloadMusicStream(music);
}

EndGameState::EndGameState()
{
}

EndGameState::~EndGameState()
{
}

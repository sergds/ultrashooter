#include "EndGameState.h"

void EndGameState::Init()
{
	endt_music = LoadMusicStream("data/dailyagony.xm");
	SetMusicVolume(endt_music, 0.5);
	PlayMusicStream(endt_music);
}

void EndGameState::Think()
{
	UpdateMusicStream(endt_music);
	ClearBackground(BLACK);
	DrawTextEx(DefaultFont, "GAME OVER", CLITERAL(Vector2){(float)800 / 2 - 150, (float)600 / 2 - 100}, 50, 1, WHITE);
	DrawTextEx(DefaultFont,TextFormat("Final Score: %i", globalscore), CLITERAL(Vector2) { (float)800 / 2 - 200, (float)600 / 2 }, 50, 1, WHITE);
	DrawTextEx(DefaultFont, TextFormat("Press [R] to return to the Main Menu"), CLITERAL(Vector2) { 0, (float)600 - 50 }, 25, 1, WHITE);
	if (IsKeyPressed(KEY_R)) {
		SwitchGameState(new MainMenuGameState());
	}
}

void EndGameState::Destroy()
{
	StopMusicStream(endt_music);
	UnloadMusicStream(endt_music);
}

EndGameState::EndGameState()
{
}

EndGameState::~EndGameState()
{
}

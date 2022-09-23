#include "EndGameState.h"
#include "globals.h"
#include "raylib.h"
#include <fstream>
#include <ios>

void EndGameState::Init()
{
	std::ifstream fl("hiscore.dat");
	if(fl.is_open()){
		fl >> topscore;
		fl.close();
	}
	endt_music = LoadMusicStream("data/dailyagony.xm");
	SetMusicVolume(endt_music, 0.5);
	PlayMusicStream(endt_music);
	if (globalscore > topscore){
		topscore = globalscore;
		std::ofstream fl("hiscore.dat", std::ios_base::trunc);
		fl << topscore;
		fl.close();
	}
}

void EndGameState::Think()
{
	UpdateMusicStream(endt_music);
	ClearBackground(BLACK);
	DrawTextEx(DefaultFont, "GAME OVER", CLITERAL(Vector2){(float)800 / 2 - 150, (float)600 / 2 - 100}, 50, 1, WHITE);
	DrawTextEx(DefaultFont,TextFormat("Final Score: %i", globalscore), CLITERAL(Vector2) { (float)800 / 2 - 200, (float)600 / 2 }, 50, 1, WHITE);
	DrawTextEx(DefaultFont,TextFormat("High Score: %i", topscore), CLITERAL(Vector2) { (float)800 / 2 - 200, (float)600 / 2 + 100}, 50, 1, WHITE);
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

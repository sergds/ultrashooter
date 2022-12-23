#include "EndGameState.h"
#include "globals.h"
#include "nlohmann/detail/conversions/from_json.hpp"
#include "raylib.h"
#include "UserData.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <ios>
#include "GUI.h"
using json = nlohmann::json;

void EndGameState::Init()
{
	std::ifstream fl("userdata.usud");
	if(fl.is_open()){
		json j;
		fl >> j;
		auto ud = j.get<UserData>();
		topscore = ud.hiscore;
		fl.close();
	}

	endt_music = LoadMusicStream("data/dailyagony.xm");
	SetMusicVolume(endt_music, 0.5);
	PlayMusicStream(endt_music);
	if (globalscore > topscore){
		UserData ud;
		ud.hiscore = globalscore;
		topscore = globalscore;
		std::ofstream fl("userdata.usud", std::ios_base::trunc);
		json j = ud;
		fl << j;
		fl.close();
	}
}

void EndGameState::Think()
{
	UpdateMusicStream(endt_music);
	ClearBackground(BLACK);
	if (GUI::ButtonCenter(470, 40, "В Меню")) {
		SwitchGameState(new MainMenuGameState());
	}
	if(frames < 661){
		DrawTextEx(DefaultFont, "GAME OVER", CLITERAL(Vector2){(float)800 / 2 - 150, (float)600 / 2 - 100}, 50, 1, WHITE);
		DrawTextEx(DefaultFont,TextFormat("Final Score: %i", globalscore), CLITERAL(Vector2) { (float)800 / 2 - 200, (float)600 / 2 }, 50, 1, WHITE);
		DrawTextEx(DefaultFont,TextFormat("High Score: %i", topscore), CLITERAL(Vector2) { (float)800 / 2 - 200, (float)600 / 2 + 100}, 50, 1, WHITE);
		//DrawTextEx(DefaultFont, TextFormat("Press [R] to return to the Main Menu"), CLITERAL(Vector2) { 0, (float)600 - 50 }, 25, 1, WHITE);
	} else {
		DrawTextEx(DefaultFont, "GLOBAL SCOREBOARD", CLITERAL(Vector2){(float)800 / 2 - 210, (float)600 / 2 - 200}, 50, 1, WHITE);
		DrawTextEx(DefaultFont, "Work In Progress ;)", CLITERAL(Vector2){(float)800 / 2 - 210, (float)600 / 2}, 50, 1, WHITE);
		//DrawTextEx(DefaultFont, TextFormat("Press [R] to return to the Main Menu"), CLITERAL(Vector2) { 0, (float)600 - 50 }, 25, 1, WHITE);
	}
	++frames;
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

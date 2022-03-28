#include "MainMenuGameState.h"
#include "GameplayGameState.h"

void MainMenuGameState::Init()
{
	logger.Log("Entering Main Menu!");
	bg = LoadTexture("data/sprites/bg_menu.png");
	enter = LoadTexture("data/sprites/menu_enter.png");
	logo = LoadTexture("data/sprites/menu_logo.png");
	menu_music = LoadMusicStream("data/menu_music.ogg");
	menu_music.looping = true;
	PlayMusicStream(menu_music);
}

void MainMenuGameState::Think()
{
	UpdateMusicStream(menu_music);
	DrawTexture(bg, 0, 0, WHITE);
	DrawTexture(logo, 300, 50, WHITE);
	if ((int)round(GetTime()) % 2) {
		DrawTexture(enter, 100, 300, WHITE);
	}
	if (IsKeyPressed(KEY_ENTER)) {
		StopMusicStream(menu_music);
		SwitchGameState(new GameplayGameState);
	}
}

void MainMenuGameState::Destroy()
{
	StopMusicStream(menu_music);
	UnloadMusicStream(menu_music);
	UnloadTexture(bg);
	UnloadTexture(enter);
	UnloadTexture(logo);
}

MainMenuGameState::MainMenuGameState()
{
}

MainMenuGameState::~MainMenuGameState()
{
}

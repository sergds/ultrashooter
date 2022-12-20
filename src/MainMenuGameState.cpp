#include "MainMenuGameState.h"
#include "GameplayGameState.h"
#include "Logger.h"
#include "ResourceSystem.h"
#include "Networking.h"
#include <thread>

void MainMenuGameState::Init()
{
	logger.Log("Entering Main Menu!");
	//bg = ResourceSystem::getInstance().GetResourceByFileName("data/sprites/bg_menu.png")->GetData();
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
	//ClearBackground(BLACK);
	switch (multiplayer_stage)
	{
	case 0:
		DrawTexture(bg, 0, 0, WHITE);
		DrawTexture(logo, 300, 50, WHITE);
		DrawText("Press [M] for online Multiplayer", 10, 10, 20, WHITE);
		if ((int)round(GetTime()) % 2) {
			DrawTexture(enter, 100, 300, WHITE);
		}
		if (IsKeyPressed(KEY_ENTER) && !IsKeyDown(KEY_LEFT_ALT)) {
			StopMusicStream(menu_music);
			SwitchGameState(new GameplayGameState);
			return;
		}
		if (IsKeyPressed(KEY_M)) {
			multiplayer_stage = 1;
			SetMusicVolume(menu_music, 0.3);
		}
		break;
	case 1:
		if (IsKeyPressed(KEY_M)) {
			multiplayer_stage = 0;
			SetMusicVolume(menu_music, 1);
		}
		DrawTexture(bg, 0, 0, CLITERAL(Color){100, 100, 100, 255});
		DrawText("Press [M] to go back", 10, 10, 20, WHITE);
		DrawTextPro(DefaultFont, "Multiplayer!", CLITERAL(Vector2){800 / 2 - 125, (float)(600 / 4 + sin(GetTime()) * 4)}, CLITERAL(Vector2){50,0},sin(GetTime()*2), 50, 1, WHITE);
		DrawText("Press [C] to connect", 800 / 2 - 150, 280, 20, WHITE);
		DrawText("Press [H] to host", 800 / 2 - 150, 300, 20, WHITE);
		if (IsKeyPressed(KEY_H)) {
			multiplayer_stage = 3;
		}
		if (IsKeyPressed(KEY_C)) {
			multiplayer_stage = 2;
		}
		break;
	case 2:
		logger.Log("Unimplemented multiplayer menu action");
		multiplayer_stage = 0;
		break;
	case 3:
		if (!networking) {
			Networking::getInstance().Init();
		}
		Networking::getInstance().Host();
		multiplayer_stage = 4;
		break;
	case 4:
		DrawText("Press [M] to return to the main menu", 10, 10, 20, WHITE);
		DrawTexture(bg, 0, 0, CLITERAL(Color){100, 100, 100, 255});
		DrawTextPro(DefaultFont, "Multiplayer Lobby!", CLITERAL(Vector2){800 / 2 - 125, (float)(600 / 4 + sin(GetTime()) * 4)}, CLITERAL(Vector2){50, 0}, sin(GetTime() * 2), 50, 1, WHITE);
		DrawText("Gamemode: Versus", 800 / 2 - 150, 280, 20, WHITE);
		if(Networking::getInstance().GetAuthority())
			DrawText("Waiting for player...", 800 / 2 - 150, 300, 20, WHITE);
		if (IsKeyPressed(KEY_M)) {
			multiplayer_stage = 0;
			Networking::getInstance().DestroyHost();
			SetMusicVolume(menu_music, 1);
		}
		break;
	default:
		break;
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

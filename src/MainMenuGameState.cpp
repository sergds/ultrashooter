#include "MainMenuGameState.h"
#include "GameplayGameState.h"
#include "Logger.h"
#include "Networking.h"
#include <thread>
#include "GUI.h"
#include "globals.h"

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
	if(leavingMenu){
		SwitchGameState(new GameplayGameState);
		return;
	}
	switch (multiplayer_stage)
	{
	case 0:
		DrawTexture(bg, 0, 0, WHITE);
		DrawTexture(logo, 300, 50, WHITE);
		//DrawText("Press [M] for online Multiplayer", 10, 10, 20, WHITE);
		//if ((int)round(GetTime()) % 2) {
		//	DrawTexture(enter, 100, 300, WHITE);
		//}
		if ((IsKeyPressed(KEY_ENTER) || GUI::ButtonCenter( 240, 50, "МОЧИТЬ НЕМЦЕВ")) && !IsKeyDown(KEY_LEFT_ALT)) {
			StopMusicStream(menu_music);
			//SwitchGameState(new GameplayGameState);
			leavingMenu = true;
			return;
		}
		if (GUI::ButtonCenter(300, 50, "Мультиплеер")) {
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
		GUI::WavyLabelCenter(100, "Мультиплеер");
		//DrawText("Press [C] to connect", 800 / 2 - 150, 280, 20, WHITE);
		//DrawText("Press [H] to host", 800 / 2 - 150, 300, 20, WHITE);
		if (GUI::ButtonCenter(280, 50, "Создать Игру")) {
			multiplayer_stage = 3;
		}
		if (GUI::ButtonCenter(340, 50, "Подключение")) {
			multiplayer_stage = 2;
		}
		break;
	case 2:
		logger.Log("Unimplemented multiplayer menu action");
		SetMusicVolume(menu_music, 1);
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
		GUI::WavyLabelCenter(100, "Лобби");
		DrawText("Gamemode: Versus", 800 / 2 - 150, 280, 20, WHITE);
		if(Networking::getInstance().GetAuthority())
			DrawText("Waiting for player...", 800 / 2 - 150, 300, 20, WHITE);
		if (IsKeyPressed(KEY_M) || GUI::ButtonCenter(470, 50.f, "Вернуться в меню")) {
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

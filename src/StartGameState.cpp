#include "StartGameState.h"
#include "AlsoStartGameState.h"
#include "Logger.h"
#include "Networking.h"
#include "globals.h"
#include "raylib.h"
#include <cstring>
#include <sstream>
#include <string>
#include <thread>

void StartGameState::Init()
{
	networking = false;
	logger.Log("Initialized StartGameState!");
	logger.Log("===== Game Init stage 2! =====");
	logger.Log("===== Checking game data =====");
#ifndef __ANDROID__ 
	if (FileExists("data/fonts/ocrabeckerrus_lat.otf") && FileExists("data/fonts/defaultfont.fnt") && FileExists("data/tink.wav") && FileExists("data/sprites/bg_menu.png") && FileExists("data/sprites/menu_enter.png") && FileExists("data/sprites/menu_logo.png") && FileExists("data/menu_music.ogg"))
	{
		logger.Log("Data is fine.");
	}
	else {
		logger.Log("Data is incomplete. game wouldn't run. Quitting Shortly.");
		CloseWindow();
	}
#endif // !__ANDROID__
	ocra = LoadFontEx("data/fonts/ocrabeckerrus_lat.otf", 50, 0, NULL);
	//int chars = 0;
	//int* codepoints = LoadCodepoints(charset, &chars);
	//DefaultFont = LoadFontEx("data/LiberationSans-Regular.ttf", 50, codepoints, chars);
	DefaultFont = LoadFont("data/fonts/defaultfont.fnt");
	logger.Log("Initialized Fonts!");
	bullet = LoadTexture("data/sprites/bullet.png");
	enemy = LoadTexture("data/sprites/hihitler.png");
	enemy2 = LoadTexture("data/sprites/hihitler2.png");
	death1 = LoadSound("data/hihitler_sounds/death1.wav");
	death2 = LoadSound("data/hihitler_sounds/death2.wav");
	speak1 = LoadSound("data/hihitler_sounds/speak1.wav");
	speak2 = LoadSound("data/hihitler_sounds/speak2.wav");
	sc = LoadSound("data/hihitler_sounds/sheisse-koph.wav");
	SetSoundVolume(death1, 0.8);
	SetSoundVolume(death2, 0.8);
	SetSoundVolume(speak1, 0.6);
	SetSoundVolume(speak2, 0.6);
	SetSoundVolume(sc, 1);
	Image tmp = LoadImageFromTexture(bullet);
	ImageResize(&tmp, tmp.width / 2, tmp.height / 2);
	bullet = LoadTextureFromImage(tmp);
	UnloadImage(tmp);
	// Attempt to init networking.
	if (Networking::getInstance().Init() == 0) {
		networking = true; // Let everything use it.
		logger.Log("Initialized networking!");
		logger.Log("Using Default Network TickRate of " + std::to_string(NET_TICRATE));
		net_ticrate = NET_TICRATE;
		std::thread netthd(NetThread);
		netthrd = new std::thread(std::move(netthd));
	}
	Color color{ 0,255,0,255 };
	col = color;
	m_binitialized = true;
	Sound tink = LoadSound("data/tink.wav");
	PlaySound(tink);
	#ifdef GITHASH
	logger.Log(TextFormat("GIT VERSION: %s", STRINGIFY(GITHASH)));
	#endif
}

void StartGameState::Think()
{
	if (m_binitialized) {
		ClearBackground(BLACK);
		Vector2 pos {0,0};
		Vector2 pos1 { 0,20 };
		DrawTextEx(ocra, "Loading...", pos, 20, 1, col);
		DrawTextEx(ocra, "Loaded!", pos1, 20, 1, col);
		DrawTextEx(ocra, buildinfo, CLITERAL(Vector2){0,40}, 20, 1, col);
		#ifdef GITHASH
		DrawTextEx(ocra, TextFormat("GIT VERSION: %s", STRINGIFY(GITHASH)), CLITERAL(Vector2){0, (float)GetRenderHeight() - 20}, 20, 1, RED); // Потенциально опасно, может вызвать проблемы при изменении поведения CMake
		#endif

		if (col.a == 252) {
			WaitTime(1.5);
		}
		if(col.a >= 10)
			col.a -= 3;
		if (col.a <= 10){
			col.a = 0;
			SwitchGameState(new AlsoStartGameState);
		}
	}
}

void StartGameState::Destroy()
{
}

StartGameState::StartGameState()
{

}

StartGameState::~StartGameState()
{
	delete& col;
}
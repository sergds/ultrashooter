#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "globals.h"
#include "GameState.h"
#include "StartGameState.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

bool fullscreenfailsafe = false;

int WinMain(int argc,char* argv[]) {
#ifndef __ANDROID__ 
	if (!DirectoryExists("data")) {
		logger.Log("Error! Game Data Not Found!");
		return 1;
	}
#endif
	InitWindow(800, 600, "Ultra Shooter!");
	InitAudioDevice();
#ifdef __ANDROID__ 
	ToggleFullscreen();
#endif
	logger.Log("=========== New Log ==============");
	SetTargetFPS(60);
	logger.Log(buildinfo);
	logger.Log("Loading Ultra Shooter!");
	while (!WindowShouldClose() && IsWindowReady()) {
		// Alt+Enter = Fullscreen.
		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_ENTER)) {
			if (!fullscreenfailsafe) {
				ToggleFullscreen();
				if(IsWindowFullscreen()){
					HideCursor();
				}
				else
				{
					ShowCursor();
				}
				fullscreenfailsafe = true;
			}
		}
		else {
			fullscreenfailsafe = false;
		}
		BeginDrawing();
		if (gs == nullptr) {
			ClearBackground(BLACK);
			DrawText("Loading...", 0, 0, 20, WHITE);
		}
		if (gs != nullptr)
			gs->Think();
		EndDrawing();
		// ???? ????????? ???? ?? ??????, ?? ????????? ?????????
		if (gs == nullptr) {
			gs = new StartGameState;
			gs->Init();
		}
	}
	logger.Log("=========== End of Log ==============");
	return 0;
}

// ??? ????? ????? MSVC. 
int main(int argc,char* argv[]) {
	WinMain(argc,argv);
}
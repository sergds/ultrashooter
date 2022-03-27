#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "globals.h"
#include "GameState.h"
#include "StartGameState.h"

int WinMain(int argc,void* argv[]) {
	if (!DirectoryExists("data")) {
		logger.Log("Error! Game Data Not Found!");
		return 1;
	}
	InitWindow(800, 600, "Ultra Shooter!");
	//ToggleFullscreen();
	logger.Log("=========== New Log ==============");
	SetTargetFPS(60);
	logger.Log(buildinfo);
	logger.Log("Loading Ultra Shooter!");
	// Если состояние игры не задано, то поставить Начальное
	while (!WindowShouldClose() && IsWindowReady()) {
		BeginDrawing();
		if (gs == nullptr) {
			ClearBackground(BLACK);
			DrawText("Loading...", 0, 0, 20, WHITE);
		}
		if (gs != nullptr)
			gs->Think();
		EndDrawing();
		if (gs == nullptr) {
			gs = new StartGameState;
			gs->Init();
		}
	}
	logger.Log("=========== End of Log ==============");
	return 0;
}
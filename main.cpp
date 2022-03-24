#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "globals.h"
#include "GameState.h"
#include "StartGameState.h"

int WinMain(int argc, void* argv[]) {
	InitWindow(800, 600, "Ultra Shooter!");
	logger.Log("=========== New Log ==============");
	SetTargetFPS(60);
	logger.Log("Loading Ultra Shooter!");
	// Если состояние игры не задано, то поставить Начальное
	while (!WindowShouldClose()) {
		BeginDrawing();
		if (gs == nullptr) {
			ClearBackground(BLACK);
			DrawText("Loading...", 20, 560, 20, WHITE);
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
#include "globals.h"
Logger logger;
GameState* gs = nullptr;

// Меняет состояние игры.
void SwitchGameState(GameState* gamestate)
{
	delete gs;
	gs = nullptr;
	gs = gamestate;
	gs->Init();
}

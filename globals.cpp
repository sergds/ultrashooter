#include "globals.h"
Logger logger;
GameState* gs = nullptr;

// ������ ��������� ����.
void SwitchGameState(GameState* gamestate)
{
	delete gs;
	gs = nullptr;
	gs = gamestate;
	gs->Init();
}

#include "StartGameState.h"

void StartGameState::Init()
{
	logger.Log("Initialized StartGameState!");
	ocra = LoadFont("data/ocrabeckerrus_lat.otf");
	Color color{ 0,255,0,255 };
	col = color;
	m_binitialized = true;
}

void StartGameState::Think()
{
	if (m_binitialized) {
		ClearBackground(BLACK);
		Vector2 pos;
		pos.x = 0;
		pos.y = 0;
		DrawTextEx(ocra, "Initialized!", pos, 20, 1, col);
		if(col.a >= 10)
			col.a -= 2;
		if (col.a <= 10){
			col.a = 0;
			SwitchGameState(nullptr);
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
	delete& ocra;
	delete& col;
}

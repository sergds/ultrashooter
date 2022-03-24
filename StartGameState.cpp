#include "StartGameState.h"
#include "AlsoStartGameState.h"

void StartGameState::Init()
{
	logger.Log("Initialized StartGameState!");
	InitAudioDevice();
	logger.Log("Initialized Audio!");
	ocra = LoadFont("data/ocrabeckerrus_lat.otf");
	Sound tink = LoadSound("data/tink.wav");
	PlaySound(tink);
	Color color{ 0,255,0,255 };
	col = color;
	WaitTime(100);
	m_binitialized = true;
}

void StartGameState::Think()
{
	if (m_binitialized) {
		ClearBackground(BLACK);
		Vector2 pos {0,0};
		Vector2 pos1 { 0,20 };
		DrawTextEx(ocra, "Loading...", pos, 20, 1, col);
		DrawTextEx(ocra, "Loaded!", pos1, 20, 1, col);
		if(col.a >= 10)
			col.a -= 4;
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
	delete& ocra;
	delete& col;
}

#include "AlsoStartGameState.h"
#include "MainMenuGameState.h"

void AlsoStartGameState::Init()
{
	logger.Log("Initialized AlsoStartGameState!");
	madeby = LoadTexture("data/fonts/prebaked/prebaked_madeby.png");
}

void AlsoStartGameState::Think()
{
	ClearBackground(BLACK);
	Vector2 pos{ 0,0 };
	//DrawTextEx(DefaultFont, "Сделал SergDS", CLITERAL(Vector2) { 280, 280 }, 40, 1, WHITE);
	//DrawTexture(DefaultFont.texture, 0, 0, WHITE);
	DrawTexture(madeby, (800 / 2) - madeby.width / 2, (600 / 2) - madeby.height, MAROON);
	DrawTextEx(DefaultFont, "hold any key or LMB to skip", CLITERAL(Vector2){ ((float)800 / 2) - 150, ((float)600 / 2) + 100 }, 30, 1, CLITERAL(Color){100,100,100,255});
	if (m_tics == 200) {
		//DrawTextEx(DefaultFont, "Для более весёлых уроков инфы!", CLITERAL(Vector2) { 100, (10 * (float)sin(GetTime() * 2) + 320) }, 40, 1, WHITE);
		//int count = 0;
		//int* codepoints = LoadCodepoints("Для более весёлых уроков инфы!", &count);
		//DrawTextCodepoints(DefaultFont, codepoints, count, CLITERAL(Vector2) { 100, (10 * (float)sin(GetTime() * 2) + 320) }, 40, 1, WHITE);
		madeby = LoadTexture("data/fonts/prebaked/prebaked_madeby2.png");
		
	}
	if (m_tics >= 600) {
		SwitchGameState(new MainMenuGameState);
	}
	if (GetKeyPressed() != 0 || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if(m_tics <= 200)
			madeby = LoadTexture("data/fonts/prebaked/prebaked_madeby2.png");
		m_tics += 200;
	}
	++m_tics;
}

void AlsoStartGameState::Destroy()
{
	UnloadTexture(madeby);
}

AlsoStartGameState::AlsoStartGameState()
{
}

AlsoStartGameState::~AlsoStartGameState()
{
}

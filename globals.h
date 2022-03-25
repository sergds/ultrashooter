#pragma once
#include <raylib.h>
#include <vector>
#include "Logger.h"
#include "GameState.h"
extern const char* buildinfo;
extern Music menu_music;
extern const char charset[204];
extern Font ocra;
extern Font DefaultFont;
extern Logger logger;
extern class GameState* gs;
extern void SwitchGameState(GameState* gs);
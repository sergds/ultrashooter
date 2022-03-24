#pragma once
#include <raylib.h>
#include "Logger.h"
#include "GameState.h"
extern Logger logger;
extern class GameState* gs;
extern void SwitchGameState(GameState* gs);
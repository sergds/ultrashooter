#pragma once
#include <raylib.h>
#include <vector>
#include <algorithm>
#include "Logger.h"
#include "GameState.h"
#include "Actor.h"
extern std::vector<Actor*> actors;
extern std::vector<Actor*> pending_actors;
extern std::vector<Actor*> dereg_pending_actors;
extern double gameplaytimestamp;
extern int globalscore;
extern const char* buildinfo;
extern Texture bullet;
extern Texture enemy;
extern Texture enemy2;
extern Music menu_music;
extern Music game_music;
extern Music endt_music;
extern Sound death1;
extern Sound death2;
extern Sound speak1;
extern Sound speak2;
extern Sound sc;
extern const char charset[204];
extern Font ocra;
extern Font DefaultFont;
extern Logger logger;
extern class GameState* gs;
extern void SwitchGameState(GameState* gs);
extern void RegisterActor(Actor* actor);
extern void DeregisterActor(Actor* actor);
extern void ProcessActors();
const int MAX_ENEMY_SPEED = 13;
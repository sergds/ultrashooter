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
extern const char* buildinfo;
extern Texture bullet;
extern Music menu_music;
extern const char charset[204];
extern Font ocra;
extern Font DefaultFont;
extern Logger logger;
extern class GameState* gs;
extern void SwitchGameState(GameState* gs);
extern void RegisterActor(Actor* actor);
extern void DeregisterActor(Actor* actor);
extern void ProcessActors();
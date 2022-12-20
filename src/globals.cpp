#include "globals.h"
#include "Networking.h"
#include <chrono>
#include <thread>

#ifndef __ANDROID__ 
const char* buildinfo = TextFormat("Ultra Shooter build: %s %s", __DATE__, __TIME__);
#else
const char* buildinfo = TextFormat("Ultra Shooter !ANDROID! build: %s %s", __DATE__, __TIME__);
#endif
std::vector<Actor*> actors;
std::vector<Actor*> pending_actors;
std::vector<Actor*> dereg_pending_actors;
double gameplaytimestamp = 0;
int globalscore = 0;
int topscore = 0;
bool networking = false;
bool freezeframe = false;
std::thread* netthrd;
bool quitting = false;
Logger logger;
Music menu_music;
Music game_music;
Music endt_music;
Sound death1;
Sound death2;
Sound speak1;
Sound speak2;
Sound sc;
Texture bullet;
Texture enemy;
Texture enemy2;
Font ocra;
Font DefaultFont;
GameState* gs = nullptr;
float net_ticrate = 60;


void SwitchGameState(GameState* gamestate)
{
	gs->Destroy();
	delete gs;
	gs = nullptr;
	gs = gamestate;
	if(gs != nullptr)
		gs->Init();
}

void NetThread()
{
	while (!quitting) {
		Networking::getInstance().Frame();
		std::this_thread::sleep_for(std::chrono::milliseconds(NET_TICRATE));
	}
}

void RegisterActor(Actor* actor) {
	if(actor != nullptr)
		pending_actors.emplace_back(actor);
}


void DeregisterActor(Actor* actor) {
	if (actor != nullptr)
		dereg_pending_actors.emplace_back(actor);
}

void ProcessActors() {
	if (pending_actors.size() != 0) {
		for (auto it = pending_actors.begin(); it != pending_actors.end(); it++) {
			actors.emplace_back(*it);
		}
		pending_actors.clear();
	}
	if (dereg_pending_actors.size() != 0) {
		for (auto it = dereg_pending_actors.begin(); it != dereg_pending_actors.end(); it++) {
			if ((*it) != nullptr) {
				actors.erase(std::remove(actors.begin(), actors.end(), (*it)), actors.end());
				//delete (*it);
				(*it) = nullptr;
			}
		}
		dereg_pending_actors.clear();
	}
}
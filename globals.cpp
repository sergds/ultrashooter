#include "globals.h"

const char* buildinfo = TextFormat("Ultra Shooter v1.0 build: %s %s", __DATE__, __TIME__);
std::vector<Actor*> actors;
std::vector<Actor*> pending_actors;
std::vector<Actor*> dereg_pending_actors;
Logger logger;
Music menu_music;
Texture bullet;
Font ocra;
Font DefaultFont;
GameState* gs = nullptr;
const char charset[204] = "�����������娸����������������������������������������������������.(){}[];':1234567890AaBbCcDdEeFfGgHhIiJjKkLlMmOoPpQqRrSsTtUuVvWwXxYyZz!,.? ";

// ������ ��������� ����.
void SwitchGameState(GameState* gamestate)
{
	gs->Destroy();
	delete gs;
	gs = nullptr;
	gs = gamestate;
	if(gs != nullptr)
		gs->Init();
}

// ������������ ������ � ������ (��� ���� ����� ������ ���� ��������� ��� Think())
void RegisterActor(Actor* actor) {
	pending_actors.emplace_back(actor);
}
// ��������� ������ � ������� �� ��������.
void DeregisterActor(Actor* actor) {
	dereg_pending_actors.emplace_back(actor);
}

// ������ ���������� ������ ����, ����� ���������� ������ ������ � ������ actors, � ��������� ��� ��������.
void ProcessActors() {
	if (pending_actors.size() != 0) {
		for (auto it = pending_actors.begin(); it != pending_actors.end(); it++) {
			actors.emplace_back(*it);
		}
		pending_actors.clear();
	}
	if (dereg_pending_actors.size() != 0) {
		for (auto it = dereg_pending_actors.begin(); it != dereg_pending_actors.end(); it++) {
			actors.erase(std::remove(actors.begin(), actors.end(),  ( * it)), actors.end());
		}
		dereg_pending_actors.clear();
	}
}
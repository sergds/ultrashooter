#include "globals.h"

const char* buildinfo = TextFormat("Ultra Shooter v1.0 build: %s %s", __DATE__, __TIME__);
std::vector<Actor*> actors;
std::vector<Actor*> pending_actors;
std::vector<Actor*> dereg_pending_actors;
double gameplaytimestamp = 0;
int globalscore = 0;
Logger logger;
Music menu_music;
Texture bullet;
Texture enemy;
Texture enemy2;
Font ocra;
Font DefaultFont;
GameState* gs = nullptr;
const char charset[204] = "јаЅб¬в√гƒд≈е®Є∆ж«з»и…й кЋлћмЌнќоѕп–р—с“т”у‘ф’х÷ц„чЎшўщЏъџы№ьЁэёюя€.(){}[];':1234567890AaBbCcDdEeFfGgHhIiJjKkLlMmOoPpQqRrSsTtUuVvWwXxYyZz!,.? ";

// ћен€ет состо€ние игры.
void SwitchGameState(GameState* gamestate)
{
	gs->Destroy();
	delete gs;
	gs = nullptr;
	gs = gamestate;
	if(gs != nullptr)
		gs->Init();
}

// –егистрирует јктора в списке (дл€ того чтобы каждый кадр вызывалс€ его Think())
void RegisterActor(Actor* actor) {
	if(actor != nullptr)
		pending_actors.emplace_back(actor);
}

// ƒобавл€ет актора в очередь на удаление.
void DeregisterActor(Actor* actor) {
	if (actor != nullptr)
		dereg_pending_actors.emplace_back(actor);
}

// ƒолжно вызыватьс€ каждый кадр, чтобы зареганные акторы попали в список actors, и удалились уже ненужные.
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
			//delete (*it);
			(*it) = nullptr;
		}
		dereg_pending_actors.clear();
	}
}
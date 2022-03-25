#include "globals.h"
const char* buildinfo = TextFormat("Ultra Shooter v1.0 build: %s %s", __DATE__, __TIME__);
Logger logger;
Music menu_music;
Font ocra;
Font DefaultFont;
GameState* gs = nullptr;
const char charset[204] = "ÀàÁáÂâÃãÄäÅå¨¸ÆæÇçÈèÉéÊêËëÌìÍíÎîÏïÐðÑñÒòÓóÔôÕõÖö×÷ØøÙùÚúÛûÜüÝýÞþßÿ.(){}[];':1234567890AaBbCcDdEeFfGgHhIiJjKkLlMmOoPpQqRrSsTtUuVvWwXxYyZz!,.? ";

// Ìåíÿåò ñîñòîÿíèå èãðû.
void SwitchGameState(GameState* gamestate)
{
	gs->Destroy();
	delete gs;
	gs = nullptr;
	gs = gamestate;
	if(gs != nullptr)
		gs->Init();
}

#pragma once
#include "GameState.h"
#include <cmath>
class MainMenuGameState :
    public GameState
{
private:
    Texture bg;
    Texture logo;
    Texture enter;
    int multiplayer_stage = 0; // 0 - No multiplayer | 1 - Connect/Host menu | 2 - Connect menu | 3 - Host menu | 4 - Lobby | 5 - Player setup
    int multiplayer_timer = 0;
public:
    void Init();
    void Think();
    void Destroy();
    MainMenuGameState();
    ~MainMenuGameState();
};


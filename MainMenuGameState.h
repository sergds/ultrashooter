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
public:
    void Init();
    void Think();
    void Destroy();
    MainMenuGameState();
    ~MainMenuGameState();
};


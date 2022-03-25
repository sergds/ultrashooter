#pragma once
#include "GameState.h"
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


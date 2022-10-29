#pragma once
#include "GameState.h"
#include "MainMenuGameState.h"
class EndGameState :
    public GameState
{
public:
    void Init();
    void Think();
    void Destroy();
    EndGameState();
    ~EndGameState();
private:
    int frames = 0;
};


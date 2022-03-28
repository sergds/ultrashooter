#pragma once
#include "GameState.h"
#include "MainMenuGameState.h"
class EndGameState :
    public GameState
{
private:
    Music music;
public:
    void Init();
    void Think();
    void Destroy();
    EndGameState();
    ~EndGameState();
};


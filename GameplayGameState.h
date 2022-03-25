#pragma once
#include "GameState.h"
#include <vector>
class GameplayGameState :
    public GameState
{
private:
    //Texture bg;
public:
    void Init();
    void Think();
    void Destroy();
    GameplayGameState();
    ~GameplayGameState();
};


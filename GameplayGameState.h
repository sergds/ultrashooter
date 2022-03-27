#pragma once
#include "GameState.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"

class GameplayGameState :
    public GameState
{
private:
    Texture bg;
    int score = 0;
    int prosrano = 0;
public:
    void Init();
    void Think();
    void Destroy();
    GameplayGameState();
    ~GameplayGameState();
};


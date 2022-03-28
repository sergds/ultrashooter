#pragma once
#include "GameState.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "Player.h"
#include "Enemy.h"
#include "EndGameState.h"

class GameplayGameState :
    public GameState
{
private:
    Texture bg;
    int score = 0;
    int prosrano = 0;
    int m_spawntics = 300;
public:
    void Init();
    void Think();
    void Destroy();
    GameplayGameState();
    ~GameplayGameState();
};


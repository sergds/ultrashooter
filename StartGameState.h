#pragma once
#include "GameState.h"
// Начальное состояние (заставка).
class StartGameState :
    public GameState
{
private:
    Font ocra;
    Color col;
    bool m_binitialized = false;
public:
    void Init();
    void Think();
    void Destroy();
    StartGameState();
    ~StartGameState();
};


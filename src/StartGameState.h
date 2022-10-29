#pragma once
#include "GameState.h"
#include "globals.h"
// ��������� ��������� (��������).
class StartGameState :
    public GameState
{
private:
    Color col;
    bool m_binitialized = false;
public:
    void Init();
    void Think();
    void Destroy();
    StartGameState();
    ~StartGameState();
};


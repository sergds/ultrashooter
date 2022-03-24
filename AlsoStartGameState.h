#pragma once
#include "GameState.h"
class AlsoStartGameState :
    public GameState
{
private:
    bool m_binitialized = false;
public:
    void Init();
    void Think();
    void Destroy();
    AlsoStartGameState();
    ~AlsoStartGameState();
};


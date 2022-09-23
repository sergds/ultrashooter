#pragma once
#include "GameState.h"
class AlsoStartGameState :
    public GameState
{
private:
    bool m_binitialized = false;
    int m_tics = 0;
    Texture madeby;
    Texture reDL;
public:
    void Init();
    void Think();
    void Destroy();
    AlsoStartGameState();
    ~AlsoStartGameState();
};


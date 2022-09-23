#pragma once
#include "globals.h"
// Базовый класс для игровых состояний.
class GameState
{
private:
	bool m_binitialized = false;
public:
	virtual void Init();
	virtual void Think();
	virtual void Destroy();
	GameState();
	~GameState();
};


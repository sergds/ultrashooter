#pragma once
#include "globals.h"
// ������� ����� ��� ������� ���������.
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


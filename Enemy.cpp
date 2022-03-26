#include "Enemy.h"

Enemy::Enemy()
{
	m_sprite = LoadTexture("data/sprites/hihitler.png");
	m_sprite2 = LoadTexture("data/sprites/hihitler2.png");
	m_origin = { (float)m_sprite.height / 2,(float)m_sprite.width / 2 };
	m_pos = { m_origin.x, m_origin.y };
}

Enemy::~Enemy()
{
}

void Enemy::Think()
{
	if ((int)GetTime() % 2) {
		DrawTexture(m_sprite, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	else {
		DrawTexture(m_sprite2, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	m_pos.y += 50 * GetFrameTime();
}

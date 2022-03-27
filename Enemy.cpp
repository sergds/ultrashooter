#include "Enemy.h"

Enemy::Enemy()
{
	m_sprite = LoadTexture("data/sprites/hihitler.png");
	m_sprite2 = LoadTexture("data/sprites/hihitler2.png");
	m_origin = { (float)m_sprite.height / 2,(float)m_sprite.width / 2 };
	m_pos = { (float)GetRandomValue((int)m_origin.x, 600 - (int)m_origin.x), m_origin.y};
}

Enemy::~Enemy()
{
}

Vector2 Enemy::GetPosition()
{
	return m_pos;
}

Vector2 Enemy::GetOrigin()
{
	return m_origin;
}

std::string Enemy::GetName()
{
	return m_name;
}

float Enemy::GetRotation()
{
	return m_rotdeg;
}

void Enemy::Think()
{
	if (!(m_tics % 30)) {
		if (m_talk == false) {
			m_talk = true;
		}
		else {
			m_talk = false;
		}
	}
	if (m_talk) {
		DrawTexture(m_sprite2, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	} 
	else {
		DrawTexture(m_sprite, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	m_pos.y += 50 * GetFrameTime();
	++m_tics;
}

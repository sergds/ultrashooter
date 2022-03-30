#include "Enemy.h"

Enemy::Enemy()
{
	// Предзагруженные текстурки хихитлера
	m_sprite = enemy;
	m_sprite2 = enemy2;
	m_origin = { (float)m_sprite.width / 2,(float)m_sprite.height / 2 };
	m_pos = { (float)GetRandomValue((int)m_origin.x, 800 - (int)m_origin.x), -100};
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

void Enemy::Die()
{
	if (GetRandomValue(0, 1) == 0) {
		PlaySoundMulti(death1);
	}
	else {
		PlaySoundMulti(death2);
	}
	if (GetRandomValue(0, 100) >= 90) {
		PlaySoundMulti(sc);
	}
}

void Enemy::Think()
{
	if (!(m_tics % 30)) {
		if (m_talk == false) {
			m_talk = true;
			if (GetRandomValue(0, 100) >= 85) {
				if (GetRandomValue(0, 1) == 0) {
					PlaySoundMulti(speak2);
				}
				else {
					PlaySoundMulti(speak1);
				}
			}
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
	m_pos.y += std::min<double>((70 + (GetTime() - gameplaytimestamp) * 3) * GetFrameTime(), MAX_ENEMY_SPEED);
	++m_tics;
}

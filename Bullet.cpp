#include "Bullet.h"

// Конструктор по умолчанию.
Bullet::Bullet()
{
	m_sprite = bullet; // Пуля грузится один раз при запуске игры, иначе память потечёт.
	m_origin = { (float)m_sprite.width / 2,(float)m_sprite.height / 2 };
	m_pos = { m_origin.x, m_origin.y };
}

// Конструктор с возможностью указать место появления пули.
Bullet::Bullet(Vector2 Pos)
{
	m_sprite = bullet; // Пуля грузится один раз при запуске игры, иначе память потечёт.
	m_origin = { (float)m_sprite.width / 2,(float)m_sprite.height / 2 };
	m_pos = Pos;
}

Bullet::~Bullet()
{
	//UnloadTexture(m_sprite);
}

Vector2 Bullet::GetPosition()
{
	return m_pos;
}

Vector2 Bullet::GetOrigin()
{
	return m_origin;
}

std::string Bullet::GetName()
{
	return m_name;
}

float Bullet::GetRotation()
{
	return m_rotdeg;
}

void Bullet::Think()
{
	DrawTexture(m_sprite, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	m_pos.y -= 400 * GetFrameTime();
}

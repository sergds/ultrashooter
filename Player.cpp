#include "Player.h"

Player::Player()
{
	m_sprite = LoadTexture("data/sprites/stalin.png");
	m_sprite2 = LoadTexture("data/sprites/stalin_grin.png");
	Image tmp = LoadImageFromTexture(m_sprite);
	ImageResize(&tmp, tmp.width / 2, tmp.height / 2);
	m_sprite = LoadTextureFromImage(tmp);
	UnloadImage(tmp);
	tmp = LoadImageFromTexture(m_sprite2);
	ImageResize(&tmp, tmp.width / 2, tmp.height / 2);
	m_sprite2 = LoadTextureFromImage(tmp);
	UnloadImage(tmp);
	m_origin = { (float)m_sprite.height / 2,(float)m_sprite.width / 2 };
	m_pos = { m_origin.x, 600 - m_origin.y * 2 };
}

Player::~Player()
{
	UnloadTexture(m_sprite);
	UnloadTexture(m_sprite2);
}

void Player::Think()
{
	if (m_grintics == 0) {
		DrawTexture(m_sprite, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	else {
		DrawTexture(m_sprite2, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	if (IsKeyDown(KEY_RIGHT)) {
		m_pos.x += 400 * GetFrameTime();
	}
	if (IsKeyDown(KEY_LEFT)) {
		m_pos.x -= 400 * GetFrameTime();
	}
	if (IsKeyPressed(KEY_SPACE)) {
		m_grintics = 25;
	}
	if (m_grintics > 0)
		--m_grintics;
}

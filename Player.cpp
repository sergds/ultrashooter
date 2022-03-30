#include "Player.h"
#include "Bullet.h"
#include "globals.h"

Player::Player()
{
	shot = LoadSound("data/shot.wav");
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
	m_origin = { (float)m_sprite.width / 2,(float)m_sprite.height / 2 };
	m_pos = { m_origin.x, 650 - m_origin.y * 2 };
}

Player::~Player()
{
	UnloadTexture(m_sprite);
	UnloadTexture(m_sprite2);
	UnloadSound(shot);
}

Vector2 Player::GetPosition()
{
	return m_pos;
}

Vector2 Player::GetOrigin()
{
	return m_origin;
}

std::string Player::GetName()
{
	return m_name;
}

float Player::GetRotation()
{
	return m_rotdeg;
}

void Player::Think()
{
	if (m_grintics <= 0) {
		DrawTexture(m_sprite, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	else {
		DrawTexture(m_sprite2, m_pos.x - m_origin.x, m_pos.y - m_origin.y, WHITE);
	}
	if (IsKeyDown(KEY_RIGHT) && m_pos.x <= 800 - m_origin.x / 2) {
		m_pos.x += 450 * GetFrameTime();
	}
	if (IsKeyDown(KEY_LEFT) && m_pos.x >= 0 + m_origin.x) {
		m_pos.x -= 450 * GetFrameTime();
	}
	if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) {
		if (m_grintics <= 0) {
			//Bullet bullet(CLITERAL(Vector2){m_pos.x, m_pos.y - 50});
			RegisterActor(new Bullet(CLITERAL(Vector2) { m_pos.x, m_pos.y - 50 }));
			m_grintics = 20;
			SetSoundPitch(shot, (float)GetRandomValue(70, 90) / 100);
			PlaySound(shot);
		}
	}
	else {
		if (m_grintics > 0)
			m_grintics -= 1;
	}
	if (m_grintics > 0)
		--m_grintics;
}

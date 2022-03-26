#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

Vector2 Actor::GetPosition()
{
	return m_pos;
}

Vector2 Actor::GetOrigin()
{
	return m_origin;
}

float Actor::GetRotation()
{
	return m_rotdeg;
}

void Actor::Think()
{
}

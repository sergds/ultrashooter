#pragma once
#include "Actor.h"
class Bullet :
    public Actor
{
private:
	Vector2 m_pos = { 0,0 }; //Position of actor
	Vector2 m_origin = { 0,0 }; //Center of actor
	float m_rotdeg = 0; //Rotation in Degrees
	Texture m_sprite;
public:
	std::string name = "Bullet";
	Bullet();
	~Bullet();
	void Think();
};


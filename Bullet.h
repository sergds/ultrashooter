#pragma once
#include "Actor.h"
#include "globals.h"
class Bullet :
    public Actor
{
private:
	Vector2 m_pos = { 0,0 }; //Position of actor
	Vector2 m_origin = { 0,0 }; //Center of actor
	float m_rotdeg = 0; //Rotation in Degrees
	Texture m_sprite;
	std::string m_name = "Bullet";
public:
	Bullet();
	Bullet(Vector2 Pos);
	~Bullet();
	Vector2 GetPosition();
	Vector2 GetOrigin();
	std::string GetName();
	float GetRotation();
	void Think();
};


#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{
private:
	Vector2 m_pos = { 0,0 }; //Position of actor
	Vector2 m_origin = { 0,0 }; //Center of actor
	float m_rotdeg = 0; //Rotation in Degrees
	Texture m_sprite;
	Texture m_sprite2;
	int m_tics = 0;
	bool m_talk = false;
	std::string m_name = "Enemy";
public:
	Enemy();
	~Enemy();
	Vector2 GetPosition();
	Vector2 GetOrigin();
	std::string GetName();
	float GetRotation();
	void Think();
};


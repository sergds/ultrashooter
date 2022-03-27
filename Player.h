#pragma once
#include "Actor.h"
class Player :
    public Actor
{
private:
	Vector2 m_pos = { 0,0 }; //Position of actor
	Vector2 m_origin = { 0,0 }; //Center of actor
	float m_rotdeg = 0; //Rotation in Degrees
	Texture m_sprite;
	Texture m_sprite2;
	Sound shot;
	int m_grintics = 0;
	std::string m_name = "Player";
public:
	Player();
	~Player();
	Vector2 GetPosition();
	Vector2 GetOrigin();
	std::string GetName();
	float GetRotation();
    void Think();
};


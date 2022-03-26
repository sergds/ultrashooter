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
	int m_grintics = 0;
public:
	std::string name = "Player";
	Player();
	~Player();
    void Think();
};


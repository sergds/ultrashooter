#pragma once
#include <raylib.h>
#include <string>
class Actor
{
private:
	Vector2 m_pos = { 0,0 }; //Position of actor
	Vector2 m_origin = { 0,0 }; //Center of actor
	float m_rotdeg = 0; //Rotation in Degrees
	Texture m_sprite;
public:
	std::string name = "Unnamed Actor";
	Actor();
	~Actor();
	Vector2 GetPosition();
	Vector2 GetOrigin();
	float GetRotation();
	virtual void Think();
};


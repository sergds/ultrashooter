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
	std::string m_name = "Unnamed Actor";
public:
	Actor();
	~Actor();
	virtual Vector2 GetPosition();
	virtual Vector2 GetOrigin();
	virtual std::string GetName() = 0;
	virtual float GetRotation();
	virtual void Think();
};


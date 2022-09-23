#include "RTexture.h"

RTexture::RTexture(std::string filename)
{
	data = LoadTexture(filename.c_str());
}

RTexture::~RTexture()
{
	UnloadTexture(data);
}

Texture* RTexture::GetData()
{
	return &data;
}

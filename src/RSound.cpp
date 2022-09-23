#include "RSound.h"

RSound::RSound()
{
}

RSound::RSound(std::string filename)
{
	data = LoadSound(filename.c_str());
}

RSound::~RSound()
{
	UnloadSound(data);
}

Sound* RSound::GetData()
{
	return &data;
}

#pragma once
#include <string>
class RResource
{
public:
	RResource();
	RResource(std::string filename);
	~RResource();
	void* GetData();

};


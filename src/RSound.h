#pragma once
#include "RResource.h"
#include "globals.h"
class RSound :
    public RResource
{
public:
    RSound();
    RSound(std::string filename);
    ~RSound();
    Sound* GetData();
private:
    Sound data;
};
#pragma once
#include "RResource.h"
#include "globals.h"
class RTexture :
    public RResource
{
public:
    RTexture(std::string filename);
    ~RTexture();
    Texture* GetData();
private:
    Texture data;
};
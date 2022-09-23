#pragma once
#include "RResource.h"
#include "globals.h"
class RFont :
    public RResource
{
public:
    RFont();
    RFont(std::string filename);
    ~RFont();
    Font* GetData();
private:
    Font data;
};
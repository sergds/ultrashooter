#pragma once
#include "globals.h"
#include "RResource.h"
#include "RSound.h"
#include "RFont.h"
#include "RTexture.h"
#include <map>
#include <string>
class ResourceSystem
{
public:
    static ResourceSystem& getInstance()
    {
        static ResourceSystem instance;
        return instance;
    }
    RResource* LoadResource(std::string file);
    RResource* GetResourceByFileName(std::string file);
    void UnloadResource(std::string file);
private:
    ResourceSystem() {};
    std::map<std::string, RResource*> resources; // Filename -|- RResource ptr
public:
    ResourceSystem(ResourceSystem const&) = delete;
    void operator=(ResourceSystem const&) = delete;
};


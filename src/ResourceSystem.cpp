#include "ResourceSystem.h"

RResource* ResourceSystem::LoadResource(std::string file)
{
	RResource* rres;
	std::string fileext = file.substr(file.find_last_of(".") + 1);
	if (fileext == "wav" || fileext == "ogg") {
		rres = new RSound(file);
	}
	else if (fileext == "ttf" || fileext == "otf" || fileext == "fnt") {
		rres = new RFont(file);
	}
	else if (fileext == "tga" || fileext == "png" || fileext == "jpg") {
		rres = new RTexture(file);
	}
	resources.emplace(file, rres);
	return rres;
}

RResource* ResourceSystem::GetResourceByFileName(std::string file)
{
	auto search = resources.find(file);
	if (search != resources.end()) {
		logger.Log("[ResourceSystem] found existing RResource!");
		return (*search).second;
	} else {
		return this->LoadResource(file);
	}
	//return nullptr;
}

void ResourceSystem::UnloadResource(std::string file)
{
	auto search = resources.find(file);
	if (search != resources.end()) {
		resources.erase(search);
		delete (*search).second;
	}
	else {
		return;
	}

}


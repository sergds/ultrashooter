#include "RFont.h"

RFont::RFont()
{
}

RFont::RFont(std::string filename)
{
    data = LoadFontEx(filename.c_str(), 50, 0, NULL);
}

RFont::~RFont()
{
    UnloadFont(data);
}

Font* RFont::GetData()
{
    return &data;
}

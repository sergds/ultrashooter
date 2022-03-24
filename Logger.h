#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Logger
{
private:
	std::ofstream logfile;
public:
	Logger();
	void Log(std::string msg);
	~Logger();
};


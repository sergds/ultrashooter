#include "Logger.h"

Logger::Logger()
{
	logfile.open("ultrashooter_log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
}

void Logger::Log(std::string msg)
{
	std::string mesg;
	mesg = msg;
	mesg.append("\n");
	std::cout << mesg;
	logfile.write(mesg.c_str(), mesg.size());
	logfile.flush();
}

Logger::~Logger()
{
	logfile.close();
}

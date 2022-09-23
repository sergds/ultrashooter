#include "Logger.h"

Logger::Logger()
{
#ifndef __ANDROID__ 
	logfile.open("ultrashooter_log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
#endif
}

void Logger::Log(std::string msg)
{
	std::string mesg;
	mesg = msg;
	mesg.append("\n");
	std::cout << mesg;
#ifndef __ANDROID__ 
	logfile.write(mesg.c_str(), mesg.size());
	logfile.flush();
#endif
}

Logger::~Logger()
{
	logfile.close();
}

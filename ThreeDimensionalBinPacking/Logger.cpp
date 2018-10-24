#include "Logger.h"

using namespace Stat;

Logger::Logger(std::string logPath, std::string errorPath)
{
	this->errorPath = errorPath;
	this->logPath = logPath;
}

Logger::Logger(std::string logPath)
{
	this->logPath = logPath;
	this->errorPath = logPath.append(".error");
}

Logger::~Logger(void)
{
}

void Logger::Clear() 
{
	std::ofstream fs;
	fs.open(this->logPath,std::ios_base::trunc);
	fs.close();
	fs.open(this->errorPath,std::ios_base::trunc);
	fs.close();
}

void Logger::Append(std::string record, int mode) 
{
	try {
		if (mode & ERROR) 
		{
			record.insert(0, "EXCEPTION! ");
		}

		time_t now = time(0);
		tm *ltm = 0; 
		errno_t err = localtime_s(ltm, &now);

		mode |= GENERAL;

		if (mode & GENERAL) 
		{
			std::ofstream fs;
			fs.open(this->logPath,std::ios_base::app);
			fs << "[" << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << "]:" << record.c_str() << std::endl;
			fs.close();
		}

		if ((mode & ERROR) && !this->logPath.compare(this->errorPath))
		{
			std::ofstream fs;
			fs.open(this->errorPath,std::ios_base::app);
			fs << "[" << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << "]:" << record.c_str() << std::endl;
			fs.close();
		}
	}
	catch (std::exception) 
	{
		//TODO: warn about exception
	}
}

void Logger::Append(std::string record) 
{
	this->Append(record, GENERAL);
}
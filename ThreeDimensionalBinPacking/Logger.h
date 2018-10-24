#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <exception>

namespace Stat {

	class Logger
	{
	private:
		std::string logPath;
		std::string errorPath;

	public:
		static const int GENERAL = 1;
		static const int ERROR = 2;

		Logger(std::string logPath, std::string errorPath);
		Logger(std::string logPath);
		//Logger(void);
		~Logger(void);

		void Append (std::string record, int mode);
		void Append (std::string record);
		void Clear ();
	};
}

#pragma once
#include<string>
#include <mutex>
#include<iostream>
#include <fstream>

class Logger {
public:
	static Logger* GetInstance();
	void Log(const std::string& message);
	void OpenLogFile(const std::string& fileName);
	void CloseLogFile();

private:
	Logger();

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	//static Logger* s_instance;
	std::mutex m_mutex;
	std::ofstream m_logFile;
};
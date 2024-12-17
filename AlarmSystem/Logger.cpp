#include "Logger.h"


Logger::Logger() 
{
	std::cout << "Logger Initialized." << std::endl;
}

Logger& Logger::GetInstance()
{
	static Logger* s_instance = new Logger();

	return *s_instance;
}

void Logger::Log(const std::string& message)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::cout << message << std::endl;
	if (m_logFile.is_open()) {
		m_logFile << message << std::endl;
	}
}

void Logger::OpenLogFile(const std::string& fileName)
{
	m_logFile.open(fileName, std::ios::out | std::ios::app);
	if (m_logFile.is_open()) {
		Log("Log file opened.");
	}
}

void Logger::CloseLogFile()
{
	if (m_logFile.is_open()) {
		Log("Log file closed.");
		m_logFile.close();
	}
}
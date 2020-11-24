//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_LOGGER_H
#define DRENDER_LOGGER_H

#include <string>

class Logger
{
public:
	enum class LogLevel
	{
		LOG_INFO,
		LOG_WARNING,
		LOG_ERROR
	};

	static void LogInfo(const std::string& message);
	static void LogWarning(const std::string& message);
	static void LogError(const std::string& message);

private:
	static void Log(const std::string& message, LogLevel logLevel = LogLevel::LOG_INFO);

};

#endif//DRENDER_LOGGER_H

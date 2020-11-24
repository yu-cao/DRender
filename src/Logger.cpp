//
// Created by debyecao on 11/24/20.
//

#include "../include/Logger.hpp"
#include <iostream>

void Logger::Log(const std::string &message, LogLevel logLevel)
{
	switch (logLevel) {
		case Logger::LogLevel::LOG_INFO:
			std::cout << "[INFO]: ";
			break;
		case Logger::LogLevel::LOG_WARNING:
			std::cout << "[WARNING]: ";
			break;
		case Logger::LogLevel::LOG_ERROR:
			std::cout << "[ERROR]: ";
			break;
		default:
			std::cout << "Unhandled Log Level!" + std::to_string(int(logLevel)) + ", message: ";
			break;
	}
	std::cout << message << std::endl;
}

void Logger::LogInfo(const std::string &message)
{
	Log(message, LogLevel::LOG_INFO);
}

void Logger::LogWarning(const std::string& message)
{
	Log(message, LogLevel::LOG_WARNING);
}

void Logger::LogError(const std::string& message)
{
	Log(message, LogLevel::LOG_ERROR);
}
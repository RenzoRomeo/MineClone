#pragma once

#include "../core.h"

enum LogType
{
	DEBUG,
	WARNING,
	ERROR
};

inline static void LOG(LogType type, std::string message)
{
	std::cerr << "[";
	switch (type)
	{
	case LogType::DEBUG:
		std::cerr << "DEBUG";
		break;
	case LogType::WARNING:
		std::cerr << "WARNING";
		break;
	case LogType::ERROR:
		std::cerr << "ERROR";
		break;
	}
	std::cerr << "] - " << message << '\n';
}
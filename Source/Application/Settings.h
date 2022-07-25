#pragma once

#include "../core.h"

namespace Settings
{
	extern uint32_t width;
	extern uint32_t height;
	extern float mouseSensitivity;
	extern bool noclip;

	bool save(const std::string& path);
	bool load(const std::string& path);
}
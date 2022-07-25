#include "Settings.h"

namespace Settings
{
	uint32_t width = 1280;
	uint32_t height = 720;
	float mouseSensitivity = 3.0f;
	bool noclip = true;

	bool load(const std::string& path)
	{
		return true;
	}

	bool save(const std::string& path)
	{
		return true;
	}
}
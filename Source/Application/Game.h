#pragma once

#include "../core.h"

struct GameConfig
{
	uint32_t windowWidth;
	uint32_t windowHeight;
	bool fullscreen;
	bool vSync;
	const char* title;
};

namespace MineClone
{
	void init(GameConfig config);

	void run();
}
#include "Application/Game.h"

int main()
{
	GameConfig config;
	config.fullscreen = false;
	config.title = "MineClone";
	config.vSync = true;
	config.windowWidth = 1280;
	config.windowHeight = 720;

	MineClone::init(config);

	MineClone::run();

	return 0;
}
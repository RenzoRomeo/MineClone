#pragma once

#include "../core.h"

namespace Input
{
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);

	void resetOffsets();

	bool isKeyPressed(int key);

	bool isMouseButtonPressed(int button);

	double getMousePosX();

	double getMousePosY();

	double getMouseOffsetX();

	double getMouseOffsetY();
}
#include "Input.h"

namespace Input
{
	namespace
	{
		bool keyStates[GLFW_KEY_LAST] = { false };
		bool mouseButtonStates[GLFW_MOUSE_BUTTON_LAST] = { false };
		double mouseScrollX = 0.0;
		double mouseScrollY = 0.0;
		double offsetX = 0.0;
		double offsetY = 0.0;
		double xPos = 0.0;
		double yPos = 0.0;
	}
	
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouseScrollX = xoffset;
		mouseScrollY = yoffset;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key >= 0 && key < GLFW_KEY_LAST) {
			if (action == GLFW_PRESS) {
				keyStates[key] = true;
			}
			else if (action == GLFW_RELEASE) {
				keyStates[key] = false;
			}
		}
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
			if (action == GLFW_PRESS) {
				mouseButtonStates[button] = true;
			}
			else if (action == GLFW_RELEASE) {
				mouseButtonStates[button] = false;
			}
		}
	}

	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		offsetX = xpos - xPos;
		offsetY = yPos - ypos;

		xPos = xpos;
		yPos = ypos;
	}

	void resetOffsets() {
		offsetX = 0.0;
		offsetY = 0.0;
	}

	bool isKeyPressed(int key)
	{
		if (key < 0 || key >= GLFW_KEY_LAST)
			return false;
		return keyStates[key];
	}

	bool isMouseButtonPressed(int button)
	{
		if (button < 0 || button >= GLFW_MOUSE_BUTTON_LAST)
			return false;
		return mouseButtonStates[button];
	}

	double getMousePosX()
	{
		return xPos;
	}

	double getMousePosY()
	{
		return yPos;
	}

	double getMouseOffsetX()
	{
		return offsetX;
	}

	double getMouseOffsetY()
	{
		return offsetY;
	}
}



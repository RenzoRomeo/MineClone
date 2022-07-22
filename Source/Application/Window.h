#pragma once

#include "../core.h"

class Window
{
public:
	Window(uint32_t width, uint32_t height, const char* title, bool vSync = true);
	~Window();

	bool shouldClose();

	void pollEvents();

	void swapBuffers();

	void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	void close();

	inline uint32_t getWidth() const { return m_width; }

	inline uint32_t getHeight() const { return m_height; }

	inline float getAspectRatio() const { return (float)m_width / (float)m_height; }

private:
	uint32_t m_width, m_height;
	GLFWwindow* m_nativeWindow;
};
#include "Window.h"
#include "Logging.h"
#include "Input.h"

Window::Window(uint32_t width, uint32_t height, const char* title, bool vSync)
	: m_width(width), m_height(height)
{
	if (!glfwInit())
	{
		LOG(LogType::ERROR, "Failed to initialize GLFW");
		exit(EXIT_FAILURE);
	}

	m_nativeWindow = glfwCreateWindow(m_width, m_height, title, NULL, NULL);

	if (!m_nativeWindow)
	{
		LOG(LogType::ERROR, "Failed to create GLFW window");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_nativeWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG(LogType::ERROR, "Failed to initialize GLAD");
		exit(EXIT_FAILURE);
	}

	glfwSwapInterval(vSync);

	glfwSetKeyCallback(m_nativeWindow, Input::keyCallback);
	glfwSetMouseButtonCallback(m_nativeWindow, Input::mouseButtonCallback);
	glfwSetCursorPosCallback(m_nativeWindow, Input::mousePositionCallback);
	glfwSetScrollCallback(m_nativeWindow, Input::scrollCallback);

	glfwSetInputMode(m_nativeWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, m_width, m_height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
}

Window::~Window()
{
	glfwDestroyWindow(m_nativeWindow);
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_nativeWindow);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_nativeWindow);
}

void Window::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close()
{
	glfwSetWindowShouldClose(m_nativeWindow, true);
}
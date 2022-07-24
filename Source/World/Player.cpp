#include "Player.h"

#include "../Application/Input.h"
#include "../Application/Logging.h"

void Player::Camera::updateVectors()
{
	front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Player::Player()
	: m_velocity({0,0,0})
{
	m_config = Configuration();

	m_camera = Camera();
	m_camera.front = { 1, 0, 0 };
	m_camera.up = m_camera.worldUp;
	m_camera.right = { 0, 0, 1 };
	m_camera.pitch = 0.0f;
	m_camera.yaw = -90.0f;
	m_camera.position = { 0,0,0 };

	m_camera.updateVectors();
}

Player::Player(glm::vec3 position)
	: m_velocity({ 0,0,0 })
{
	m_config = Configuration();

	m_camera = Camera();
	m_camera.front = { 1, 0, 0 };
	m_camera.up = m_camera.worldUp;
	m_camera.right = { 0, 0, 1 };
	m_camera.pitch = 0.0f;
	m_camera.yaw = -90.0f;
	m_camera.position = position;

	m_camera.updateVectors();
}

Player::Player(glm::vec3 position, glm::vec3 front)
	: m_velocity({ 0,0,0 })
{
}

void Player::update(float dt)
{
	LOG(m_camera.position);
	processMouse(dt);
	processKeyboard(dt);
}

void Player::processMouse(float dt)
{
	m_camera.yaw += Input::getMouseOffsetX() * m_config.mouseSensitivity * dt;
	m_camera.pitch += Input::getMouseOffsetY() * m_config.mouseSensitivity * dt;

	Input::resetOffsets();

	if (m_camera.pitch > 89.0f) m_camera.pitch = 89.0f;
	if (m_camera.pitch < -89.0f) m_camera.pitch = -89.0f;

	m_camera.updateVectors();
}

void Player::processKeyboard(float dt)
{
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
	m_velocity.z = 0.0f;

	if (Input::isKeyPressed(GLFW_KEY_W)) {
		m_velocity += m_camera.front;
	}
	if (Input::isKeyPressed(GLFW_KEY_S)) {
		m_velocity -= m_camera.front;
	}
	if (Input::isKeyPressed(GLFW_KEY_D)) {
		m_velocity += m_camera.right;
	}
	if (Input::isKeyPressed(GLFW_KEY_A)) {
		m_velocity -= m_camera.right;
	}
	if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
		m_velocity += m_camera.worldUp;
	}
	if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
		m_velocity -= m_camera.worldUp;
	}

	if (glm::length(m_velocity) > 0.1f)
	{
		m_velocity = glm::normalize(m_velocity) * m_config.movementSpeed * dt;
		m_camera.position += m_velocity;
	}
}

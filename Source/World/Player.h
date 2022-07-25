#pragma once

#include "../core.h"

class Player
{
public:
	struct Camera
	{
		float yaw;
		float pitch;
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp = { 0,1,0 };

		void updateVectors();
	};

public:
	Player();
	Player(glm::vec3 position);
	Player(glm::vec3 position, glm::vec3 front);

	void update(float dt);

	inline glm::vec3 getPosition() const { return m_camera.position; }

	inline glm::vec3 getFront() const { return m_camera.front; }

	inline const Camera& getCamera() const { return m_camera; }

private:
	void processMouse(float dt);
	void processKeyboard(float dt);

private:
	Camera m_camera;
	glm::vec3 m_velocity;
	float m_movementSpeed;
	float m_height = 2.0f;
};
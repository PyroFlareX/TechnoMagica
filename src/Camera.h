#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Util/Input.h"

class Camera
{
public:
	Camera(sf::RenderWindow* p_win);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	void move(glm::vec3& movement);
	void rotate(glm::vec3& rotationOffset);

	~Camera();
private:
	sf::RenderWindow* p_window;
	float lerp;
	float yaw = 0.0f;
	float pitch = 0.0f;
};


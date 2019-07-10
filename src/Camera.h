#pragma once

#include <SFML/Graphics.hpp>

#include "Util/Input.h"
#include "Entity.h"

class Camera : public Entity
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
};


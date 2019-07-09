#include "Camera.h"

Camera::Camera(sf::RenderWindow* p_win)
{
	p_window = p_win;
	lerp = 1.05f;
}


void Camera::move(glm::vec3& movement)
{
	cameraPos += movement * lerp;
	movement = glm::vec3(0.0f);
}

Camera::~Camera()
{

}
